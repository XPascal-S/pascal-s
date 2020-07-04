import argparse
import os

version = '0.1.1'

src = "examples/hello_world.ps"
dst = "build"

default_assembler = "C:\work\cpp\pascal-s\cmake-build-debug\src\compiler\llvm-pascal-s-r.exe"
default_optimized_assembler = "C:/work/cpp/pascal-s/cmake-build-debug/src/compiler/optimized-compiler.exe"


def str2bool(v):
    if v.lower() in ('yes', 'true', 't', 'y', '1'):
        return True
    elif v.lower() in ('no', 'false', 'f', 'n', '0'):
        return False
    else:
        raise argparse.ArgumentTypeError('Unsupported value encountered.')


parser = argparse.ArgumentParser()
parser.add_argument('--assembler',
                    default=default_assembler,
                    type=str, help='Assembler of Pascal-S')
parser.add_argument('--enable-optimize-default', type=str2bool, nargs='?', const=True, default=False,
                    help='Enable Default Optimized Assembler of Pascal-S')
parser.add_argument('--c-linker', default='g++', type=str, help='Linker')
parser.add_argument('--library', type=str, default=[], help='Linked libraries')
parser.add_argument('--version', type=str2bool, nargs='?', const=True, default=False, help='Print Version')
parser.add_argument('--env', type=str2bool, nargs='?', const=True, default=False,
                    help='Print the environment of pascal')
parser.add_argument('--use-self-main', type=str2bool, nargs='?', const=True, default=False,
                    help='Use user-defined main lib instead of default')
parser.add_argument('--work-dir', type=str, help='Working directory')
parser.add_argument('--src', type=str, help='Source path')
parser.add_argument('--out', default="build", type=str, help='Output path')
parser.add_argument('--out-ir', type=str, help='Output IR Code, enum of {json, yml, fmt, binary, console}')
parser.add_argument('--out-token', type=str, help='Output tokens, enum of {json, yml, fmt, binary, console}')
parser.add_argument('--out-ast', type=str, help='Output ast, enum of {json, yml, fmt, binary, console}')

args = parser.parse_args()

if args.version:
    print(version)
    exit(0)

if args.src is None:
    print('src option is required, use --help to find options')
    exit(0)

if isinstance(args.library, str):
    args.library = args.library.split(',')

if not args.use_self_main:
    args.library.append("C:/work/cpp/pascal-s/lib/libstdps.a")

if args.enable_optimize_default and args.assembler == default_assembler:
    args.assembler = default_optimized_assembler

# print(args)

if not os.path.isfile(args.src):
    print('source file should not be directory')

if not os.path.exists(args.out):
    os.mkdir(args.out)
object_file = os.path.abspath(
    os.path.join(args.out, os.path.splitext(os.path.basename(args.src))[0] + '.o'))

asm_options = [
    args.assembler,
]

asm_options += [
    '--src=' + os.path.abspath(args.src),
    '--o=' + object_file,
]

if args.out_ir is not None:
    asm_options.append('--out-ir=' + args.out_ir)

if args.out_token is not None:
    asm_options.append('--out-token=' + args.out_token)

if args.out_ast is not None:
    asm_options.append('--out-ast=' + args.out_ast)

asm = ' '.join(asm_options)
# print(asm)
print('assembling...')
print('generated', object_file)
asm_result = os.popen(asm).readlines()
if len(asm_result) > 0:
    print('\n'.join(map(lambda s: s.strip('\n'), asm_result)))

link = ' '.join([
                    args.c_linker,
                    '-o', os.path.abspath(
        os.path.join(args.out, os.path.splitext(os.path.basename(args.src))[0])),
                    object_file,
                ] + args.library)
# print(link)
print('linking...')
link_result = os.popen(link).readlines()
if len(link_result) > 0:
    print('\n'.join(map(lambda s: s.strip('\n'), link_result)))
