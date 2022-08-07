#pragma once

#include "LibJson.h"

template <class T> bool JsonOptionalValue<T>::Presented() { return presented; }