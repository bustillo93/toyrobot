#pragma once

#include "map/IMap.hpp"
#include <gmock/gmock.h>

namespace map::mocks
{

class MapMock final : public map::IMap
{
public:
    MapMock() = default;
    ~MapMock() override = default;

    MOCK_METHOD(bool, IsWithinRange, (const Point&), (const, override));
};

} // namespace map::mocks
