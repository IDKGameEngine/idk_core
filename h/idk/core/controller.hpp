// #pragma once

// #include <glm/glm.hpp>


// namespace idk::core
// {
//     class ICharacterController
//     {
//     public:
//         glm::vec3 move_;
//         glm::vec3 look_;

//         ICharacterController(): move_(0.0f), look_(0.0f) {  };
//         virtual void move(const glm::vec3 &moveDelta) = 0;
//         virtual void look(const glm::vec3 &lookDelta) = 0;
//         void getMotion(glm::vec3 &moveDelta, glm::vec3 &lookDelta)
//         {
//             moveDelta = move_;
//             lookDelta = look_;
//             move_ *= 0.0f;
//             look_ *= 0.0f;
//         }
//     };

//     class TestCharacterController: public ICharacterController
//     {
//     public:
//         float moveSpeed = 1.0f;
//         float lookSpeed = 1.0f;

//         virtual void move(const glm::vec3 &moveDelta) final
//         {
//             move_ += moveSpeed*moveDelta;
//         }

//         virtual void look(const glm::vec3 &lookDelta) final
//         {
//             look_ += lookSpeed*lookDelta;
//         }

//     };

// }

