#include "surface.hh"

namespace rt {

const Material* Surface::material() const noexcept {
  return material_.get();
}

Surface& Surface::SetMaterial(std::unique_ptr<Material> material) noexcept {
  material_ = std::move(material);
  return *this;
}

Surface& Surface::AddTransformation(
    std::unique_ptr<Transformation> transform) noexcept {
  transforms_.push_back(std::move(transform));
  return *this;
}

Surface& Surface::SetTime(std::chrono::milliseconds time) noexcept {
  inv_transform_ = Matrix4<>{};
  for (auto& transform : transforms_) {
    transform->SetTime(time);
    inv_transform_ = *transform->Inverse() * inv_transform_;
  }
  inv_t_transform_ = inv_transform_.Transpose();
  return *this;
}

std::optional<Intersection> Surface::Hit(const Ray& ray) const {
  auto inter = [&] {
    if (transforms_.empty()) {
      return DoHit(ray);
    }
    auto origin = inv_transform_.MultiplyPoint(ray.origin);
    auto direction = inv_transform_.MultiplyVector(ray.direction);
    auto inter = DoHit({origin, direction});
    if (inter.has_value()) {
      inter->point = ray.At(inter->distance);
      inter->normal = inv_t_transform_.MultiplyVector(inter->normal).Unit();
    }
    return inter;
  }();
  if (inter.has_value()) {
    inter->front = ray.direction.Dot(inter->normal) < 0.0;
    if (!inter->front) {
      inter->normal = -inter->normal;
    }
  }
  return inter;
}

}  // namespace rt
