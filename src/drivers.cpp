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

#include "camera/camera.hpp"

#include "glm_format.hpp"

#include <format>
#include <string>

namespace raoe::camera
{
    void controller::update(double delta_time)
    {
        transform transform;
        for(auto& driver : m_drivers)
        {
            transform = driver->update(delta_time, transform);
        }

        m_view_matrix = glm::lookAt(transform.position, transform.position + transform.forward(),
                                    glm::vec3(0.0f, 1.0f, 0.0f)); // TODO: Make this up vector configurable
    }

    std::string arm::describe() const
    {
        return std::format("arm({})", m_offset);
    }

    std::string lock_position::describe() const
    {
        return std::format("lock_position({} {})", m_lock, m_position);
    }

    std::string look_at::describe() const
    {
        return std::format("look_at({}, {}, p {}, sm {}, offset {})", get_target(), m_smoothed_target, m_predictive,
                           m_smooth_factor, m_output_offset_scale);
    }

    std::string position::describe() const
    {
        return std::format("position({})", get_position());
    }
    std::string rotation::describe() const
    {
        return std::format("rotation({})", get_rotation());
    }
    std::string smooth::describe() const
    {
        return std::format("smooth(p {} s{} r{} tsf{} rsf{})", m_predictive, m_smoothed_rotation, m_smoothed_rotation,
                           m_translation_smoothness_factor, m_rotation_smoothness_factor);
    }

    std::string yaw_pitch::describe() const
    {
        return std::format("yaw_pitch({}, {})", m_yaw, m_pitch);
    }
}
