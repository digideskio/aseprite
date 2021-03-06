// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/ui/editor/pivot_helpers.h"

#include "app/pref/preferences.h"
#include "gfx/transformation.h"

namespace app {

void set_pivot_from_preferences(gfx::Transformation& t)
{
  gfx::Transformation::Corners corners;
  t.transformBox(corners);
  gfx::PointT<double> nw(corners[gfx::Transformation::Corners::LEFT_TOP]);
  gfx::PointT<double> ne(corners[gfx::Transformation::Corners::RIGHT_TOP]);
  gfx::PointT<double> sw(corners[gfx::Transformation::Corners::LEFT_BOTTOM]);
  gfx::PointT<double> se(corners[gfx::Transformation::Corners::RIGHT_BOTTOM]);
  gfx::PointT<double> pivotPos((nw + se) / 2);

  app::gen::PivotPosition pivot = Preferences::instance().selection.pivotPosition();
  switch (pivot) {
    case app::gen::PivotPosition::NORTHWEST:
      pivotPos = nw;
      break;
    case app::gen::PivotPosition::NORTH:
      pivotPos = (nw + ne) / 2.0;
      break;
    case app::gen::PivotPosition::NORTHEAST:
      pivotPos = ne;
      break;
    case app::gen::PivotPosition::WEST:
      pivotPos = (nw + sw) / 2.0;
      break;
    case app::gen::PivotPosition::EAST:
      pivotPos = (ne + se) / 2.0;
      break;
    case app::gen::PivotPosition::SOUTHWEST:
      pivotPos = sw;
      break;
    case app::gen::PivotPosition::SOUTH:
      pivotPos = (sw + se) / 2.0;
      break;
    case app::gen::PivotPosition::SOUTHEAST:
      pivotPos = se;
      break;
  }

  t.displacePivotTo(gfx::Point(pivotPos));
}

} // namespace app
