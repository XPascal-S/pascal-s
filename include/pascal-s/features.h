//
// Created by kamiyoru on 2020/5/5.
//

#ifndef PASCAL_S_FEATURES_H
#define PASCAL_S_FEATURES_H

#include "interface.h"
#include "token.h"
#include <functional>
#include <algorithm>

namespace feature {

    template<typename OStream>
    using output_tokens_t = std::function<void(const std::vector<Token *> &tokens, WriterProxy<OStream> &os)>;

    template<typename File, typename OStream, typename Error>
    using format_line_column_error_t = std::function<void(FileProxy<File> f, ErrorProxy<Error> err,
                                                          WriterProxy<OStream> &os)>;

    template<typename OStream>
    void output_tokens(const std::vector<Token *> &tokens, WriterProxy<OStream> &os) {
        os << "out tokens\n";
        for (auto &token: tokens) {
            os.write_data(fmt::format("{}:{}: {}\n", token->line, token->column, convertToString(token)));
        }
    }

    template<typename File, typename OStream, typename Error>
    void format_line_column_error(FileProxy<File> f, ErrorProxy<Error> err, WriterProxy<OStream> &os) {
        static const int show_width = 50;
        static char buffer[(show_width * 2) + 5];
        char *pBuffer = buffer;

        size_t offset = err.visit_offset();
        size_t column = err.visit_column();
        size_t length = err.visit_length();
        size_t buffer_read_l = offset - std::min<size_t>(show_width, column),
                buffer_read_r = offset + std::max<size_t>(show_width, length);
        const char *hint = err.visit_hint();
        assert(buffer_read_l >= 0);

        f.seek(buffer_read_l);
        f.read(pBuffer, buffer_read_r - buffer_read_l);
        pBuffer = pBuffer - buffer_read_l;
        for (int i = offset; i < buffer_read_r; i++) {
            if (pBuffer[i] == '\n' || pBuffer[i] == 0) {
                pBuffer[i] = 0;
                buffer_read_r = i;
            }
        }

        os.write_data(fmt::format("{}:{}: ", err.visit_line(), column));
        if (hint != nullptr) {
            os.write_data(hint);
        }
        os << '\n';

        int hl = 0;
        if (show_width < column) {
            auto h = fmt::format("(omitting {} chars) ", column - show_width);
            os.write_data(h);
            hl = h.length();
        }
        os.write_data(pBuffer + buffer_read_l) << '\n';
        os.write_data(fmt::format("{:>{}}\n", fmt::format("{:^<{}}", "", length), hl + column + length));
    }
}


#endif //PASCAL_S_FEATURES_H
