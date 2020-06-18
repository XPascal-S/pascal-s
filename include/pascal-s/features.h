//
// Created by kamiyoru on 2020/5/5.
//

#ifndef PASCAL_S_FEATURES_H
#define PASCAL_S_FEATURES_H

#include "interface.h"
#include "token.h"

namespace feature {

    template<typename OStream>
    void output_tokens(const std::vector<Token *> &tokens, WriterProxy<OStream> &os) {
        os << "out tokens\n";
        for (auto &token: tokens) {
            os.write_data(fmt::format("{}:{}: {}\n", token->line, token->column, convertToString(token)));
        }
    }

    template<typename File, typename OStream, typename Error>
    void format_line_column_error(FileProxy<File> f, ErrorProxy<Error> err, WriterProxy<OStream> &os) {

    }
}


#endif //PASCAL_S_FEATURES_H
