// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Consider this file an implementation detail. None of this is part of the
// public API.

#ifndef MEDIAPIPE_GPU_GL_TEXTURE_BUFFER_POOL_H_
#define MEDIAPIPE_GPU_GL_TEXTURE_BUFFER_POOL_H_

#include "absl/status/statusor.h"
#include "absl/synchronization/mutex.h"
#include "mediapipe/gpu/gl_texture_buffer.h"
#include "mediapipe/gpu/multi_pool.h"
#include "mediapipe/gpu/reusable_pool.h"

#include <utility>
#include <vector>

namespace mediapipe {

class GlTextureBufferPool : public ReusablePool<GlTextureBuffer> {
public:
    // Creates a pool. This pool will manage buffers of the specified dimensions,
    // and will keep keep_count buffers around for reuse.
    // We enforce creation as a shared_ptr so that we can use a weak reference in
    // the buffers' deleters.
    static std::shared_ptr<GlTextureBufferPool> Create(int width, int height, GpuBufferFormat format, int keep_count) {
        return Create({width, height, format}, {.keep_count = keep_count});
    }

    static std::shared_ptr<GlTextureBufferPool> Create(const internal::GpuBufferSpec& spec, const MultiPoolOptions& options) {
        return std::shared_ptr<GlTextureBufferPool>(new GlTextureBufferPool(spec, options));
    }

    int width() const {
        return spec_.width;
    }

    int height() const {
        return spec_.height;
    }

    GpuBufferFormat format() const {
        return spec_.format;
    }

    static absl::StatusOr<GlTextureBufferSharedPtr> CreateBufferWithoutPool(const internal::GpuBufferSpec& spec) {
        return GlTextureBuffer::Create(spec);
    }

protected:
    GlTextureBufferPool(const internal::GpuBufferSpec& spec, const MultiPoolOptions& options)
        : ReusablePool<GlTextureBuffer>(
              [this] {
                  return GlTextureBuffer::Create(spec_);
              },
              options)
        , spec_(spec) { }

    const internal::GpuBufferSpec spec_;
};

} // namespace mediapipe

#endif // MEDIAPIPE_GPU_GL_TEXTURE_BUFFER_POOL_H_
