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
    class look_at : public driver
    {
      public:
        look_at() = default;
        explicit look_at(glm::vec3 target, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
            : m_target([target]() { return target; })
            , m_up(up)
        {
        }

        explicit look_at(std::function<glm::vec3()> target, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f))
            : m_target(std::move(target))
            , m_up(up)
        {
        }

        [[nodiscard]] glm::vec3 get_target() const
        {
            if(m_target)
            {
                return m_target.value()();
            }
            else
            {
                return glm::vec3(0.0f);
            }
        }

        [[nodiscard]] glm::vec3 smoothed_target() const { return m_smoothed_target; }
        [[nodiscard]] bool predictive() const { return m_predictive; }
        void predictive(bool predictive) { m_predictive = predictive; }
        [[nodiscard]] float smooth_factor() const { return m_smooth_factor; }
        void smooth_factor(float smooth_factor) { m_smooth_factor = smooth_factor; }
        [[nodiscard]] float output_offset_scale() const { return m_output_offset_scale; }
        void output_offset_scale(float output_offset_scale) { m_output_offset_scale = output_offset_scale; }

        virtual transform update(double delta_time, transform previous_transform) override
        {
            glm::vec3 target = get_target();
            m_smoothed_target = _private::exp_smooth_towards(m_smoothed_target, target, m_smooth_factor,
                                                             m_output_offset_scale, delta_time);
            glm::quat rotation = glm::quatLookAt(glm::normalize(m_smoothed_target - previous_transform.position), m_up);

            return transform(previous_transform.position, rotation);
        }

        virtual std::string describe() const override;

      private:
        std::optional<std::function<glm::vec3()>> m_target;
        glm::vec3 m_smoothed_target;
        bool m_predictive;
        float m_smooth_factor = 0.0f;
        float m_output_offset_scale = 1.0f;
        glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    };
}