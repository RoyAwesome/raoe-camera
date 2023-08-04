/*
Copyright 2022-2023 Roy Awesome's Open Engine (RAOE)

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#pragma once

#include "glm/ext.hpp"
#include <format>

#define DECLARE_FORMATTER_IMPL(type, ns, ...)                                                                          \
    template <>                                                                                                        \
    struct ns::formatter<type>                                                                                         \
    {                                                                                                                  \
        template <typename ParseContext>                                                                               \
        constexpr auto parse(ParseContext& ctx)                                                                        \
        {                                                                                                              \
            return ctx.begin();                                                                                        \
        }                                                                                                              \
                                                                                                                       \
        template <typename FormatContext>                                                                              \
        auto format(const type& value, FormatContext& ctx)                                                             \
        {                                                                                                              \
            return format_to(ctx.out(), __VA_ARGS__);                                                                  \
        }                                                                                                              \
    };

#define DECLARE_FORMATTER(type, ...) DECLARE_FORMATTER_IMPL(type, std, __VA_ARGS__)

DECLARE_FORMATTER(glm::uvec2, "({}, {})", value.x, value.y)
DECLARE_FORMATTER(glm::uvec3, "({}, {}, {})", value.x, value.y, value.z)
DECLARE_FORMATTER(glm::uvec4, "({}, {}, {}, {})", value.x, value.y, value.z, value.w)
DECLARE_FORMATTER(glm::ivec2, "({}, {})", value.x, value.y)
DECLARE_FORMATTER(glm::ivec3, "({}, {}, {})", value.x, value.y, value.z)
DECLARE_FORMATTER(glm::ivec4, "({}, {}, {}, {})", value.x, value.y, value.z, value.w)
DECLARE_FORMATTER(glm::bvec2, "({}, {})", value.x, value.y)
DECLARE_FORMATTER(glm::bvec3, "({}, {}, {})", value.x, value.y, value.z)
DECLARE_FORMATTER(glm::bvec4, "({}, {}, {}, {})", value.x, value.y, value.z, value.w)
DECLARE_FORMATTER(glm::vec2, "({}, {})", value.x, value.y)
DECLARE_FORMATTER(glm::vec3, "({}, {}, {})", value.x, value.y, value.z)
DECLARE_FORMATTER(glm::vec4, "({}, {}, {}, {})", value.x, value.y, value.z, value.w)
DECLARE_FORMATTER(glm::mat4, "\n[{}, {}, {}, {}]\n[{}, {}, {}, {}]\n[{}, {}, {}, {}]\n[{}, {}, {}, {}]", value[0][0],
                  value[1][0], value[2][0], value[3][0], value[0][1], value[1][1], value[2][1], value[3][1],
                  value[0][2], value[1][2], value[2][2], value[3][2], value[0][3], value[1][3], value[2][3],
                  value[3][3])
DECLARE_FORMATTER(glm::mat3, "\n[{}, {}, {}]\n[{}, {}, {}]\n[{}, {}, {}]", value[0][0], value[1][0], value[2][0],
                  value[0][1], value[1][1], value[2][1], value[0][2], value[1][2], value[2][2])
DECLARE_FORMATTER(glm::mat2, "\n[{}, {}]\n[{}, {}]", value[0][0], value[1][0], value[0][1], value[1][1])
DECLARE_FORMATTER(glm::quat, "({}, {}, {}, {})", value.x, value.y, value.z, value.w)