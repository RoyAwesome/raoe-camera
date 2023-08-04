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
    class smooth : public driver
    {
      public:
        smooth() = default;
        smooth(float translation_smoothness_factor, float rotation_smoothness_factor, bool predictive)
            : m_translation_smoothness_factor(translation_smoothness_factor)
            , m_rotation_smoothness_factor(rotation_smoothness_factor)
            , m_predictive(predictive)
        {
        }

        virtual transform update(double delta_time, transform previous_transform) override
        {
            auto translation = previous_transform.position;
            auto rotation = previous_transform.rotation;

            auto translation_delta = translation - m_smoothed_translation;
            auto rotation_delta = glm::inverse(m_smoothed_rotation) * rotation;

            m_smoothed_translation +=
                translation_delta * static_cast<float>(delta_time) * m_translation_smoothness_factor;
            m_smoothed_rotation = glm::slerp(m_smoothed_rotation, rotation,
                                             static_cast<float>(delta_time) * m_rotation_smoothness_factor);

            return transform(m_smoothed_translation, m_smoothed_rotation);
        }

        virtual std::string describe() const override;

      private:
        [[nodiscard]] float output_offset_scale() const noexcept { return m_predictive ? -1.0f : 1.0f; }
        float m_translation_smoothness_factor = 1.0f;
        float m_rotation_smoothness_factor = 1.0f;

        bool m_predictive = false;
        glm::vec3 m_smoothed_translation = glm::vec3(0.0f);
        glm::quat m_smoothed_rotation = glm::identity<glm::quat>();
    };
}