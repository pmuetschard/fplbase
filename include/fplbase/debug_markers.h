// Copyright 2016 Google Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef FPLBASE_DEBUG_MARKERS_H
#define FPLBASE_DEBUG_MARKERS_H

/// @file fplbase/debug_markers.h
/// @brief Functions for inserting GL debug markers.
///
/// To enable, \#define FPLBASE_ENABLE_DEBUG_MARKERS 1

#define FPLBASE_ENABLE_DEBUG_MARKERS 1  // TODO: move to build config

#if FPLBASE_ENABLE_DEBUG_MARKERS
#include "fplbase/config.h"  // Must come first.
#include "fplbase/glplatform.h"

#if defined(PLATFORM_MOBILE) && defined(__ANDROID__) && __ANDROID_API__ < 18
extern GL_APICALL void (* GL_APIENTRY glPushDebugGroup)(GLsizei length, const GLchar *message);
extern GL_APICALL void (* GL_APIENTRY glPopDebugGroup)(void);
#endif
#endif

extern void DebugMarkersInit();

inline void PushDebugMarker(const std::string& marker) {
  (void)marker;
#if FPLBASE_ENABLE_DEBUG_MARKERS
  const char *message = marker.c_str();
  #if defined(PLATFORM_MOBILE) && defined(__ANDROID__) && __ANDROID_API__ < 18
    GL_CALL(glPushDebugGroup(marker.length(), message));
  #else
    GL_CALL(glPushDebugGroup(GL_DEBUG_SOURCE_APPLICATION, 1, marker.length(), message));
  #endif
#endif
}

inline void PopDebugMarker() {
#if FPLBASE_ENABLE_DEBUG_MARKERS
  GL_CALL(glPopDebugGroup());
#endif
}

#endif
