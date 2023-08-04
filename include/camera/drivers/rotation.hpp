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

#include <functional>
#include <optional>

namespace raoe::camera
{
    class rotation : public driver
    {
      public:
        rotation() = default;
        rotation(std::function<glm::quat()> position)
            : m_rotation(std::move(position))
        {
        }
        rotation(glm::quat rotation)
            : m_rotation([rotation]() { return rotation; })
        {
        }

        [[nodiscard]] glm::quat get_rotation() const
        {
            if(m_rotation)
            {
                return m_rotation.value()();
            }
            return glm::identity<glm::quat>();
        }
        void set_rotation(std::function<glm::quat()> rotation) { m_rotation = std::move(rotation); }
        void set_rotation(glm::quat rotation)
        {
            m_rotation = [rotation]() { return rotation; };
        }

        virtual transform update(double delta_time, transform previous_transform) override
        {
            return transform(previous_transform.position, get_rotation());
        }

        virtual std::string describe() const override;

      private:
        std::optional<std::function<glm::quat()>> m_rotation;
    };
}