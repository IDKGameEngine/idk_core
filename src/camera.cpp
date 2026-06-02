#include "idk/core/camera.hpp"



idk::Camera::Camera(float aspect, float vfov, float znear, float zfar)
:   aspect_(aspect), vfov_(vfov), znear_(znear), zfar_(zfar)
{

}


const glm::mat4& idk::Camera::getView() const
{
    if (viewDirty_)
    {
        const glm::vec3& pos = transform_.GetPosition();
        view_ = glm::lookAt(pos, pos + transform_.GetForward(), transform_.GetUp());
        viewDirty_ = false;
    }
    return view_;
}


const glm::mat4& idk::Camera::getProj() const
{
    if (projDirty_)
    {
        proj_ = glm::perspective(glm::radians(vfov_), aspect_, znear_, zfar_);
        projDirty_ = false;
    }
    return proj_;
}
