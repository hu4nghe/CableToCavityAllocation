#pragma once

#include "cavity.h"
#include "wire.h"

#include <memory>
#include <type_traits>

template <typename T>
concept electronic_component_type = 
    std::is_base_of_v<electronic_component_base,T> &&
   !std::is_same_v   <electronic_component_base,T>;

template <electronic_component_type T>
using p_component = std::shared_ptr<T>;