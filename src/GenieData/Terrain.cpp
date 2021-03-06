/*
    genie/dat - A library for reading and writing data files of genie
               engine games.
    Copyright (C) 2011 - 2013  Armin Preiml <email>
    Copyright (C) 2011 - 2013  Mikko T P

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Terrain.h"

namespace genie
{

//------------------------------------------------------------------------------
Terrain::Terrain() : Colors(), Unknown5(), Unknown7(), ElevationGraphics(),
  TerrainUnitID(), TerrainUnitDensity(),
  TerrainUnitPriority(), SWGBUnknown1()
{
  Unknown1 = 0;
  Enabled = 1;
  Name = "";
  Name2 = "";
  SLP = -1;
  Unknown3 = 0;
  SoundID = -1;
  BlendPriority = -1;
  BlendType = -1;
  Unknown6 = 0;
  FrameCount = 0;
  AngleCount = 0;
  TerrainID = 0;
  TerrainReplacementID = 0;
  NumberOfTerrainUnitsUsed = 0;
  TerrainDimensions.first = TerrainDimensions.second = -1;
}

//------------------------------------------------------------------------------
Terrain::~Terrain()
{
}

void Terrain::setGameVersion(GameVersion gv)
{
  ISerializable::setGameVersion(gv);

  TerrainBorderIDs.resize(getTerrainBorderSize());
}

//------------------------------------------------------------------------------
unsigned short Terrain::getNameSize()
{
  if (getGameVersion() >= genie::GV_SWGB)
    return 17;
  else
    return 13;
}

//------------------------------------------------------------------------------
unsigned short Terrain::getTerrainBorderSize(void)
{
  if (getGameVersion() >= genie::GV_TC)
    return 42;
  else
    return 32;
}

//------------------------------------------------------------------------------
void Terrain::serializeObject(void)
{
  serialize<int16_t>(Unknown1);
  serialize<int16_t>(Enabled);

  serialize<std::string>(Name, getNameSize());
  serialize<std::string>(Name2, getNameSize());

  serialize<int32_t>(SLP);
  serialize<float>(Unknown3);
  serialize<int32_t>(SoundID);

  if (getGameVersion() >= genie::GV_AoK)
  {
    serialize<int32_t>(BlendPriority);
    serialize<int32_t>(BlendType);
  }

  serialize<uint8_t, 3>(Colors);
  serialize<int8_t, 5>(Unknown5);
  serialize<float>(Unknown6);
  serialize<int8_t, UNKNOWN7_SIZE>(Unknown7);
  serialize<int16_t>(FrameCount);
  serialize<int16_t>(AngleCount);
  serialize<int16_t>(TerrainID);
  serialize<int16_t, ELEVATION_GRAPHICS_SIZE>(ElevationGraphics);
  serialize<int16_t>(TerrainReplacementID);
  serialize<int16_t>(TerrainDimensions);
  serialize<int16_t>(TerrainBorderIDs, getTerrainBorderSize());

  serialize<int16_t, TERRAIN_UNITS_SIZE>(TerrainUnitID);
  serialize<int16_t, TERRAIN_UNITS_SIZE>(TerrainUnitDensity);
  serialize<int8_t, TERRAIN_UNITS_SIZE>(TerrainUnitPriority);
  serialize<int16_t>(NumberOfTerrainUnitsUsed);

  if (getGameVersion() >= genie::GV_SWGB)
    serialize<int8_t, SWGBUNKNOWN1_SIZE>(SWGBUnknown1);
}

}
