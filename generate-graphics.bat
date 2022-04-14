
rmdir /s/q  "source\gen"
rmdir /s/q  "headers\gen"

mkdir "source\gen\graphics"
mkdir "headers\gen\graphics"


SET GBDK_HOME=C:/gbdk
SET PNG2ASSET=%GBDK_HOME%\bin\png2asset.exe

@echo on

%PNG2ASSET% graphics\Bullets.png -c source/gen/graphics/Bullets.c  -sw 8 -sh 8 -spr8x16 -keep_palette_order

%PNG2ASSET% graphics\PlayerPlane.png -c source/gen/graphics/PlayerPlane.c  -sw 24 -sh 16 -px 0 -py 0 -spr8x16 -keep_palette_order


%PNG2ASSET% graphics\SmallEnemyPlane.png -c source/gen/graphics/SmallEnemyPlane.c  -sw 16 -sh 16 -spr8x16 -keep_palette_order
%PNG2ASSET% graphics\SmallExplosion.png -c source/gen/graphics/SmallExplosion.c  -sw 8 -sh 16 -spr8x16 -keep_palette_order -b 2
%PNG2ASSET% graphics\MediumExplosion.png -c source/gen/graphics/MediumExplosion.c  -sw 16 -sh 16 -spr8x16 -keep_palette_order -b 2
::%PNG2ASSET% graphics\MediumEnemyPlane.png -c source/gen/graphics/MediumEnemyPlane.c  -sw 24 -sh 48 -spr8x16 -keep_palette_order

%PNG2ASSET% graphics\Year.png -c source/gen/graphics/Year.c  -sw 48 -sh 16 -px 0 -py 0 -spr8x16 -keep_palette_order -b 1
%PNG2ASSET% graphics\LaroldsJubilantJunkyard.png -c source/gen/graphics/LaroldsJubilantJunkyard.c -map -use_map_attributes -noflip  -keep_palette_order -b 1


%PNG2ASSET% graphics\PlayerPlaneMini.png -c source\gen\graphics\PlayerPlaneMini.c -map -use_map_attributes -noflip  -keep_palette_order
%PNG2ASSET% graphics\WaterBackground.png -c source\gen\graphics\WaterBackground.c -map -use_map_attributes -noflip  -keep_palette_order
%PNG2ASSET% graphics\Font.png -c source\gen\graphics\Font.c -map -use_map_attributes -noflip  -keep_palette_order
%PNG2ASSET% graphics\StartScreen.png -c source\gen\graphics\StartScreen.c -map -use_map_attributes -noflip  -keep_palette_order
%PNG2ASSET% graphics\MenuScreen.png -c source\gen\graphics\MenuScreen.c -map -use_map_attributes -noflip  -keep_palette_order -b 1
%PNG2ASSET% graphics\PlaneScreen.png -c source\gen\graphics\PlaneScreen.c -map -use_map_attributes -noflip  -keep_palette_order -b 1
%PNG2ASSET% graphics\StageText.png -c source\gen\graphics\StageText.c -map -use_map_attributes -noflip  -keep_palette_order -b 1

@echo off

:: move .h files to their proper location
FOR /R "source/gen/graphics/" %%X IN (*.h) DO (
    move "%%X" "%cd%/headers/gen/graphics/"
)