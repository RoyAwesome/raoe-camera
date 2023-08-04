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

#include <algorithm>

namespace raoe::camera
{
    class yaw_pitch : public driver
    {
      public:
        yaw_pitch(float yaw, float pitch)
            : m_yaw(std::fmod(yaw, 720.0f))
            , m_pitch(std::clamp(pitch, -85.0f, 85.0f))
        {
        }

        void rotate(float yaw, float pitch)
        {
            this->m_yaw = std::fmod(this->m_yaw + yaw, 720.0f);
            this->m_pitch = std::clamp(this->m_pitch + pitch, -85.0f, 85.0f);
        }

        [[nodiscard]] float yaw() const noexcept { return m_yaw; }
        void yaw(float yaw) noexcept { m_yaw = std::fmod(yaw, 720.0f); }

        [[nodiscard]] float pitch() const noexcept { return m_pitch; }
        void pitch(float pitch) noexcept { m_pitch = std::clamp(pitch, -85.0f, 85.0f); }

        virtual transform update(double delta_time, transform previous_transform) override
        {
            return transform {previous_transform.position,
                              glm::quat(glm::vec3(0, glm::radians(m_yaw), glm::radians(m_pitch)))};
        }

        virtual std::string describe() const override;

      private:
        float m_yaw = 0;
        float m_pitch = 0;
    };
}