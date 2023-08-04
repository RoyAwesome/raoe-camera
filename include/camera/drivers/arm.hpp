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

#include "camera/camera.hpp"

namespace raoe::camera
{
    class arm : public driver
    {
      public:
        arm() = default;
        explicit arm(const glm::vec3& offset)
            : m_offset(offset)
        {
        }

        transform update(double delta_time, transform previous_transform) override
        {
            return transform(previous_transform.position + glm::rotate(previous_transform.rotation, m_offset),
                             previous_transform.rotation);
        }

        [[nodiscard]] const glm::vec3& offset() const { return m_offset; }
        void offset(const glm::vec3& new_offset) { m_offset = new_offset; }

        virtual std::string describe() const override;

      private:
        glm::vec3 m_offset;
    };
}