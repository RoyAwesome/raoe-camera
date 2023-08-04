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
    class position : public driver
    {
      public:
        position() = default;
        position(std::function<glm::vec3()> position)
            : m_position(std::move(position))
        {
        }
        position(glm::vec3 position)
            : m_position([position]() { return position; })
        {
        }

        [[nodiscard]] glm::vec3 get_position() const
        {
            if(m_position)
            {
                return m_position.value()();
            }
            return glm::vec3(0.0f);
        }

        virtual transform update(double delta_time, transform previous_transform) override
        {
            return transform(get_position(), previous_transform.rotation);
        }

        void set_position(std::function<glm::vec3()> position) { m_position = std::move(position); }
        void set_position(glm::vec3 position)
        {
            m_position = [position]() { return position; };
        }

        virtual std::string describe() const override;

      private:
        std::optional<std::function<glm::vec3()>> m_position;
    };
}