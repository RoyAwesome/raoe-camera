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
    class lock_position : public driver
    {
      public:
        lock_position() = default;
        lock_position(glm::vec3 position, glm::bvec3 lock = glm::bvec3(true))
            : m_position(position)
            , m_lock(lock)
        {
        }

        transform update(double delta_time, transform previous_transform) override
        {
            glm::vec3 locked_position(m_lock.x ? m_position.x : previous_transform.position.x,
                                      m_lock.y ? m_position.y : previous_transform.position.y,
                                      m_lock.z ? m_position.z : previous_transform.position.z);
            return transform(locked_position, previous_transform.rotation);
        }

        [[nodiscard]] glm::vec3 position() const { return m_position; }
        void position(glm::vec3 new_position) { m_position = new_position; }

        [[nodiscard]] glm::bvec3 lock() const { return m_lock; }
        void lock(glm::bvec3 new_lock) { m_lock = new_lock; }

        virtual std::string describe() const override;

      private:
        glm::bvec3 m_lock = glm::bvec3(false);
        glm::vec3 m_position;
    };
}