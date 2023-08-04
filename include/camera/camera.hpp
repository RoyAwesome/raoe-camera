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

#include "glm/glm.hpp"

#include "glm/ext.hpp"

#include <cmath>
#include <memory>
#include <string>
#include <vector>

namespace raoe::camera
{
    namespace _private
    {
        template <typename T>
            requires std::is_same_v<T, glm::vec3> || std::is_same_v<T, glm::quat>
        T exp_smooth_towards(T current, T target, float smoothness, float output_offset_scale, double delta_time)
        {
            const float mult = 8.0f;
            float interp_to = 1.0f - std::exp((-mult * delta_time / std::max(smoothness, 0.0001f)));

            T interp = glm::lerp(current, target, interp_to);
            if(output_offset_scale - -1.0f > 0.0001f)
            {
                interp = glm::lerp(current, interp, output_offset_scale);
            }

            return interp;
        }
    }

    struct transform
    {
        glm::vec3 position;
        glm::quat rotation;

        transform()
            : position()
            , rotation(glm::identity<glm::quat>())
        {
        }

        transform(glm::vec3 in_position, glm::quat in_rotation)
            : position(in_position)
            , rotation(in_rotation)
        {
        }

        [[nodiscard]] glm::vec3 forward() const { return glm::rotate(rotation, glm::vec3(0.0f, 0.0f, -1.0f)); }
        [[nodiscard]] glm::vec3 right() const { return glm::rotate(rotation, glm::vec3(1.0f, 0.0f, 0.0f)); }
        [[nodiscard]] glm::vec3 up() const { return glm::rotate(rotation, glm::vec3(0.0f, 1.0f, 0.0f)); }
    };

    struct driver
    {
        virtual transform update(double delta_time, transform previous_transform) = 0;
        virtual [[nodiscard]] std::string describe() const = 0;
    };

    class controller
    {
      public:
        controller()
            : m_view_matrix(glm::identity<glm::mat4>())
            , m_drivers()
        {
        }
        controller(const controller&) = delete;
        controller& operator=(const controller&) = delete;

        controller(controller&& other)
            : m_view_matrix(std::move(other.m_view_matrix))
            , m_drivers(std::move(std::exchange(other.m_drivers, {})))
        {
        }
        controller& operator=(controller&& other)
        {
            m_view_matrix = std::move(other.m_view_matrix);
            m_drivers = std::move(std::exchange(other.m_drivers, {}));
            return *this;
        }

        template <typename T, typename... Args>
            requires std::derived_from<T, driver>
        controller& with(Args&&... args)
        {
            m_drivers.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
            return *this;
        }

        template <typename T>
            requires std::derived_from<T, driver>
        T* find_first()
        {
            for(auto& driver : m_drivers)
            {
                if(T* d = dynamic_cast<T*>(driver.get()))
                {
                    return d;
                }
            }
            return nullptr;
        }

        void update(double delta_time);

        [[nodiscard]] glm::mat4 view_matrix() const { return m_view_matrix; }

      private:
        glm::mat4 m_view_matrix;
        std::vector<std::unique_ptr<driver>> m_drivers;
    };
}

#include "camera/drivers/arm.hpp"
#include "camera/drivers/lock_position.hpp"
#include "camera/drivers/look_at.hpp"
#include "camera/drivers/position.hpp"
#include "camera/drivers/rotation.hpp"
#include "camera/drivers/smooth.hpp"
#include "camera/drivers/yaw_pitch.hpp"