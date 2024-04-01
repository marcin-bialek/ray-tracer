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

std::optional<Intersection> Surface::Hit(
    const Ray& ray, const std::chrono::milliseconds& time) const {
  auto inter = [&] {
    if (transforms_.empty()) {
      return DoHit(ray);
    }
    UpdateCache(time);
    auto origin = cache_->inv_transform.MultiplyPoint(ray.origin);
    auto direction = cache_->inv_transform.MultiplyVector(ray.direction);
    auto inter = DoHit({origin, direction});
    if (inter.has_value()) {
      inter->point = ray.At(inter->distance);
      inter->normal =
          cache_->inv_t_transform.MultiplyVector(inter->normal).Unit();
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

void Surface::UpdateCache(const std::chrono::milliseconds& time) const {
  if (cache_ && cache_->time == time) {
    return;
  }
  if (!cache_) {
    cache_ = std::make_unique<Cache>();
  }
  cache_->time = time;
  cache_->inv_transform = Matrix4<>{};
  for (auto& transform : transforms_) {
    transform->SetTime(time);
    cache_->inv_transform = *transform->Inverse() * cache_->inv_transform;
    cache_->inv_t_transform = cache_->inv_transform.Transpose();
  }
}

}  // namespace rt
