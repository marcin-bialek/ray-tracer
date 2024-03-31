#include "surface.hh"

namespace rt {

const Material* Surface::material() const noexcept {
  return material_.get();
}

Surface& Surface::SetMaterial(std::unique_ptr<Material> material) noexcept {
  material_ = std::move(material);
  return *this;
}

Surface& Surface::AddTransformation(const Transformation& transform) noexcept {
  if (!inv_transform_.has_value()) {
    inv_transform_.emplace();
  }
  inv_transform_ = *transform.Inverse() * *inv_transform_;
  inv_t_transform_.emplace(inv_transform_->matrix.Transpose());
  return *this;
}

std::optional<Intersection> Surface::Hit(const Ray& ray) const {
  auto inter = [&] {
    if (!inv_transform_.has_value()) {
      return DoHit(ray);
    }
    auto origin = inv_transform_->ApplyPoint(ray.origin);
    auto direction = inv_transform_->ApplyVector(ray.direction);
    auto inter = DoHit({origin, direction});
    if (inter.has_value()) {
      inter->point = ray.At(inter->distance);
      inter->normal = inv_t_transform_->ApplyVector(inter->normal).Unit();
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
