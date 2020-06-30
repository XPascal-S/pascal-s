# please move py_pascal_s.cpXX-win_YYY.pyd to your python/src/DLLs
# cmake-build-debug/src/py-module/py_pascal_s.cp37-win_amd64.pyd
#
from typing import List

import py_pascal_s


def reinterpret_pascal_s_token(tok_ptr):
    if tok_ptr.type == py_pascal_s.PascalSTokenType.Keyword:
        return py_pascal_s.reinterpret_as_keyword(tok_ptr)  # type: py_pascal_s.PascalSTokenKeyword
    elif tok_ptr.type == py_pascal_s.PascalSTokenType.Marker:
        return py_pascal_s.reinterpret_as_marker(tok_ptr)  # type: py_pascal_s.PascalSTokenMarker
    elif tok_ptr.type == py_pascal_s.PascalSTokenType.ConstantString:
        return py_pascal_s.reinterpret_as_constant_string(tok_ptr)  # type: py_pascal_s.PascalSTokenConstantString
    elif tok_ptr.type == py_pascal_s.PascalSTokenType.ConstantBoolean:
        return py_pascal_s.reinterpret_as_constant_boolean(tok_ptr)  # type: py_pascal_s.PascalSTokenConstantBoolean
    elif tok_ptr.type == py_pascal_s.PascalSTokenType.ConstantInteger:
        return py_pascal_s.reinterpret_as_constant_integer(tok_ptr)  # type: py_pascal_s.PascalSTokenConstantInteger
    elif tok_ptr.type == py_pascal_s.PascalSTokenType.ConstantReal:
        return py_pascal_s.reinterpret_as_constant_real(tok_ptr)  # type: py_pascal_s.PascalSTokenConstantReal
    elif tok_ptr.type == py_pascal_s.PascalSTokenType.ConstantChar:
        return py_pascal_s.reinterpret_as_constant_char(tok_ptr)  # type: py_pascal_s.PascalSTokenConstantChar
    elif tok_ptr.type == py_pascal_s.PascalSTokenType.Identifier:
        return py_pascal_s.reinterpret_as_identifier(tok_ptr)  # type: py_pascal_s.PascalSTokenIdentifier
    return tok_ptr


rc = """
program example();
var x,y:integer;
function gcd(a,b:integer):integer;
    begin
        if b=0 then gcd:=a
        else gcd:=gcd(b, a mod b)
    end
begin
    read_int64(x);
    read_int64(y);
    write_int64(gcd(x, y))
end
    """
rx = rc

if __name__ == '__main__':
    lexer = py_pascal_s.PascalSLexer()
    toks = lexer.lex(rc)  # type: List[py_pascal_s.PascalSToken]

    str_slice = []
    source_slice = []
    for tok in reversed(toks):
        # if tok.type != py_pascal_s.PascalSTokenType.Identifier:
        tok = reinterpret_pascal_s_token(tok)
        # print(tok.type)
        # print(tok.offset)
        # print(tok.length)
        # print(tok.line)
        # print(tok.column + 1)
        if tok.type == py_pascal_s.PascalSTokenType.Keyword:
            source_slice.append(
                f"<p><span class='lc'>{tok.line}:{tok.column + 1}:</span> "
                f"<span class='t-type'>type = TokenType.Keyword</span>, key_type = {tok.key_type}</p>")
            print(tok.key_type)
            str_slice.append(rc[tok.offset + tok.length:])
            str_slice.append(f'<span class="token keyword">{rc[tok.offset:tok.offset + tok.length]}</span>')
            rc = rc[:tok.offset]
        elif tok.type == py_pascal_s.PascalSTokenType.Marker:
            source_slice.append(
                f"<p><span class='lc'>{tok.line}:{tok.column + 1}:</span> "
                f"<span class='t-type'>type = TokenType.Marker</span>, marker_type = {tok.marker_type}</p>")
            print(tok.marker_type)
            str_slice.append(rc[tok.offset + tok.length:])
            str_slice.append(f'<span class="token marker">{rc[tok.offset:tok.offset + tok.length]}</span>')
            rc = rc[:tok.offset]
        elif tok.type == py_pascal_s.PascalSTokenType.Identifier:
            source_slice.append(
                f"<p><span class='lc'>{tok.line}:{tok.column + 1}:</span> "
                f"<span class='t-type'>type = TokenType.Identifier</span>, content = {tok.content}</p>")
            print(tok.content)
            str_slice.append(rc[tok.offset + tok.length:])
            str_slice.append(f'<span class="token identifier">{rc[tok.offset:tok.offset + tok.length]}</span>')
            rc = rc[:tok.offset]
        elif tok.type == py_pascal_s.PascalSTokenType.ConstantString:
            source_slice.append(
                f"<p><span class='lc'>{tok.line}:{tok.column + 1}:</span> "
                f"<span class='t-type'>type = TokenType.ConstantString</span>, attr = {tok.attr}</p>")
            print(tok.attr)
            str_slice.append(rc[tok.offset + tok.length:])
            str_slice.append(f'<span class="token const-string">{rc[tok.offset:tok.offset + tok.length]}</span>')
            rc = rc[:tok.offset]
        elif tok.type == py_pascal_s.PascalSTokenType.ConstantBoolean:
            source_slice.append(
                f"<p><span class='lc'>{tok.line}:{tok.column + 1}:</span> "
                f"<span class='t-type'>type = TokenType.ConstantBoolean</span>, attr = {tok.attr}</p>")
            print(tok.attr)
            str_slice.append(rc[tok.offset + tok.length:])
            str_slice.append(f'<span class="token const-boolean">{rc[tok.offset:tok.offset + tok.length]}</span>')
            rc = rc[:tok.offset]
        elif tok.type == py_pascal_s.PascalSTokenType.ConstantInteger:
            source_slice.append(
                f"<p><span class='lc'>{tok.line}:{tok.column + 1}:</span> "
                f"<span class='t-type'>type = TokenType.ConstantInteger</span>, attr = {tok.attr}</p>")
            print(tok.attr)
            str_slice.append(rc[tok.offset + tok.length:])
            str_slice.append(f'<span class="token const-integer">{rc[tok.offset:tok.offset + tok.length]}</span>')
            rc = rc[:tok.offset]
        elif tok.type == py_pascal_s.PascalSTokenType.ConstantReal:
            source_slice.append(
                f"<p><span class='lc'>{tok.line}:{tok.column + 1}:</span> "
                f"<span class='t-type'>type = TokenType.ConstantReal</span>, attr = {tok.attr}</p>")
            print(tok.attr)
            print(tok.content)
            str_slice.append(rc[tok.offset + tok.length:])
            str_slice.append(f'<span class="token const-real">{rc[tok.offset:tok.offset + tok.length]}</span>')
            rc = rc[:tok.offset]
        elif tok.type == py_pascal_s.PascalSTokenType.ConstantChar:
            source_slice.append(
                f"<p><span class='lc'>{tok.line}:{tok.column + 1}:</span> "
                f"<span class='t-type'>type = TokenType.ConstantChar</span>, attr = {tok.attr}</p>")
            print(tok.attr)
            str_slice.append(rc[tok.offset + tok.length:])
            str_slice.append(f'<span class="token const-char">{rc[tok.offset:tok.offset + tok.length]}</span>')
            rc = rc[:tok.offset]
    str_slice.append(rc)
    print(rx)
    with open('C:\\Users\\kamiyoru\\Desktop\\test.html', 'w') as f:
        f.write(
            """
<html lang="en">
<head>
<title>Pascal-S-Lexer-View</title>
<meta charset="UTF-8"/>
<style>
    .const-char {
            color: #7ec699;
    }
    .const-integer {
            color: #49a8f0;
    }

    .const-boolean {
            color: #f8c555;
    }

    .identifier {
            color: #f08d49;
    }

    .keyword {
            color: #cc99cd;
    }

    .marker {
        color: #ccc;
    }

    .source-code {
        background: #2d2d2d;
        padding: 0 20px;
    }
    .lc {
        width: 8vw;
    }
    .t-type {
        width: 25vw;
    }
    .lc, .t-type {
        display: inline-block;
    }
    body  p {
        font-size: 1.5vw;
    }
    .source-mapping {
        overflow-x:scroll;
        max-height: 50vh;
    }
</style>
</head>
<body>
<div class='source-code'><pre class="language-pascal-s"><code class="language-pascal-s">{{content}}</code></pre></div>
<div class='source-mapping'>{{source-mapping}}</div>
</body>
</html>""".replace("{{content}}", ''.join(reversed(str_slice))).replace('{{source-mapping}}',
                                                                        ''.join(reversed(source_slice))))
    del lexer
