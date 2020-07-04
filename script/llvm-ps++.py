#!/usr/bin/python3

import argparse
import os
import json
import platform
import subprocess as sp

version = '0.1.3'


def str2bool(str_boolean):
    if str_boolean.lower() in ('yes', 'true', 't', 'y', '1'):
        return True
    elif str_boolean.lower() in ('no', 'false', 'f', 'n', '0'):
        return False
    else:
        raise argparse.ArgumentTypeError('Unsupported value encountered.')


def get_terminal_width():
    if platform.system() == 'Windows':
        return int(os.popen('tput cols', 'r').read())
    elif platform.system() == 'Linux':
        return int(os.popen('stty size', 'r').read().split()[1])
    else:
        return 120


def process_open_with_code(cmd):
    process = sp.Popen(cmd, stdout=sp.PIPE, stderr=sp.PIPE)
    result, err = process.communicate()
    code = process.returncode
    return code, result.decode(), err.decode()


src = "examples/hello_world.ps"
dst = "build"

default_assembler = "llvm-pascal-s-r.exe"
default_optimized_assembler = "optimized-compiler.exe"
default_link_library = "libstdps.a"

config_path = os.getenv('LLVM_PASCAL_CONFIG_PATH') or os.path.expanduser('~/.llvm-pascal-s.config')


def update_default_from_config_path():
    global default_assembler
    global default_optimized_assembler
    global default_link_library

    if os.path.exists(config_path):
        with open(config_path) as f:
            cfg = json.load(f)
        default_assembler = cfg.get('default_assembler', default_assembler)
        default_optimized_assembler = cfg.get('default_optimized_assembler', default_optimized_assembler)
        default_link_library = cfg.get('default_link_library', default_link_library)


def parser_add_arguments(p):
    p.add_argument('--assembler',
                   default=default_assembler,
                   type=str, help='Assembler of Pascal-S')
    p.add_argument('--enable-optimize-default', type=str2bool, nargs='?', const=True, default=False,
                   help='Enable Default Optimized Assembler of Pascal-S')
    p.add_argument('--c-linker', default='g++', type=str, help='Linker')
    p.add_argument('--library', type=str, default=[], help='Linked libraries')
    p.add_argument('--version', type=str2bool, nargs='?', const=True, default=False, help='Print Version')
    p.add_argument('--verbose', type=str2bool, nargs='?', const=True, default=False, help='Print Compiler Args')
    p.add_argument('--env', type=str2bool, nargs='?', const=True, default=False,
                   help='Print the environment of pascal')
    p.add_argument('--use-self-main', type=str2bool, nargs='?', const=True, default=False,
                   help='Use user-defined main lib instead of default')
    p.add_argument('--work-dir', type=str, help='Working directory')
    p.add_argument('--src', type=str, help='Source path')
    p.add_argument('--out', default="build", type=str, help='Output path')
    p.add_argument('--out-ir', type=str, help='Output IR Code, enum of {json, yml, fmt, binary, console}')
    p.add_argument('--out-token', type=str, help='Output tokens, enum of {json, yml, fmt, binary, console}')
    p.add_argument('--out-ast', type=str, help='Output ast, enum of {json, yml, fmt, binary, console}')
    return p


def work_verbose():
    verbose_format = []

    verbose_format.append([
        'ENVIRONMENTS:',
        'compiler environment variales'])

    verbose_format.append([
        f'LLVM_PASCAL_CONFIG_PATH     = {os.getenv("LLVM_PASCAL_CONFIG_PATH")}',
        'path to compiler option file (in json format)'])

    verbose_format.append(['', ''])

    verbose_format.append([
        'VARIABLES:',
        'compiler variables'])

    verbose_format.append([
        f'config_path                 = {config_path}',
        'path to compiler option file (from env or default value)'])

    verbose_format.append([
        f'default_assembler           = {default_assembler}',
        'using this to assemble pascal-s file'])

    verbose_format.append([
        f'default_optimized_assembler = {default_optimized_assembler}',
        'using this to assemble pascal-s file (optimized)'])

    verbose_format.append([
        f'default_link_library        = {default_link_library}',
        'usint this to support pascal-s runtime'])

    mx_len, mx_len2, eq_len = 0, 0, len('LLVM_PASCAL_CONFIG_PATH     = ')
    for v in verbose_format:
        mx_len = max(mx_len, len(v[0]))
        mx_len2 = max(mx_len, len(v[1]))
    if mx_len + mx_len2 > get_terminal_width():
        print('\n'.join(map(lambda v_item: v_item[0] + '\n' + (' ' * eq_len) + v_item[1] + '\n', verbose_format)))
    else:
        for i in range(len(verbose_format)):
            verbose_format[i][0] = verbose_format[i][0] + (' ' * (mx_len - len(verbose_format[i][0])))
        print('\n'.join(
            map(lambda v_item: v_item[0] + (' {' + v_item[1] + '}' if v_item[1] else ''), verbose_format)))


def main():
    update_default_from_config_path()

    args = parser_add_arguments(argparse.ArgumentParser()).parse_args()

    if args.version:
        print(version)
        exit(0)

    if args.verbose:
        work_verbose()
        exit(0)

    if args.src is None:
        print('src option is required, use --help to find options')
        exit(0)

    if isinstance(args.library, str):
        args.library = args.library.split(',')

    if not args.use_self_main:
        args.library.append(default_link_library)

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

    print('assembling...')
    asm_code, asm_result, asm_err = process_open_with_code(' '.join(asm_options))
    if len(asm_result.strip('\n')):
        print(asm_result.strip('\n'))
    if len(asm_err.strip('\n')):
        print(asm_err.strip('\n'))

    if asm_code != 0:
        print(f'assembling failed with code {asm_code}...')
        exit(asm_code)

    if not os.path.exists(object_file):
        print('generate object file', object_file, 'failed')
        exit(1)

    print('generated', object_file)
    op = os.path.abspath(os.path.join(args.out, os.path.splitext(os.path.basename(args.src))[0]))

    link_option = [
        args.c_linker,
        '-o', op,
        object_file,
    ]

    link_option += args.library

    # print(link)
    print('linking...')
    link_code, link_result, link_err = process_open_with_code(' '.join(link_option))
    if len(link_result.strip('\n')):
        print(link_result.strip('\n'))
    if len(link_err.strip('\n')):
        print(link_err.strip('\n'))
    if link_code != 0:
        print(f'linking failed with code {link_code}...')
        exit(link_code)


if __name__ == '__main__':
    main()
