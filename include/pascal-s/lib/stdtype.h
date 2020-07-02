//
// Created by kamiyoru on 2020/6/29.
//

#ifndef PASCAL_S_STD_TYPE_H
#define PASCAL_S_STD_TYPE_H

namespace pascal_s {
    using token_type_underlying_type = uint32_t;
    using keyword_type_underlying_type = uint8_t;
    using marker_type_underlying_type = uint8_t;

    using pascal_s_integer_t = int64_t;
    using pascal_s_real_t = double;

    using errno_t = uint32_t;
    using line_t = uint32_t;
    using column_t = uint32_t;
    using length_t = uint32_t;
    using offset_t = uint64_t;
}

#endif //PASCAL_S_STD_TYPE_H
