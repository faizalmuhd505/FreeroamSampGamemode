/*************************************************************************************************************************************
 *                                                                                                                                   *
 *                                                    )(   3DTryg Functions   )(                                                     *
 *                                                                                                                                   *
 * Copyright © 2017 Abyss Morgan. All rights reserved.                                                                               *
 * Contributors: Crayder, IllidanS4, Nero_3D, RyDeR, Zoutdaxv, hesambia, Neil Lamoureux, Ivan_Ino                                    *
 *                                                                                                                                   *
 * Download: https://github.com/AbyssMorgan/SA-MP/tree/master/include/SAM                                                            *
 * Publication: http://forum.sa-mp.com/showthread.php?t=591010                                                                       *
 * Website: http://8.ct8.pl                                                                                                          *
 *                                                                                                                                   *
 * Plugins: MapAndreas, ColAndreas, YSF, Streamer, FCNPC                                                                             *
 * Modules: FoxForeach, Foreach                                                                                                      *
 * Internal Modules: Stream3D, Line3D, Actor, ATM, Anims                                                                             *
 *                                                                                                                                   *
 * File Version: 4.2.0                                                                                                               *
 * SA:MP Version: 0.3.7 (REQUIRE)                                                                                                    *
 * MapAndreas Version: 1.2.1                                                                                                         *
 * ColAndreas Version: 1.4.0                                                                                                         *
 * YSF Version: R18-2 (kurta999)                                                                                                     *
 * Streamer Version: 2.9.0                                                                                                           *
 * FCNPC Version: 1.7.0                                                                                                              *
 *                                                                                                                                   *
 * 3DTryg FindZ Precision:                                                                                                           *
 * 1. ColAndreas   - The most accurate precision with ColAndreas plugin.                                                             *
 * 2. MapAndreas   - Average precision MapAndreas plugin.                                                                            *
 *                                                                                                                                   *
 * Foreach Types:                                                                                                                    *
 * 1. FoxForeach                                                                                                                     *
 * 2. YSIForeach                                                                                                                     *
 * 3. GetPlayerPoolSize                                                                                                              *
 *                                                                                                                                   *
 * Compiler Options:                                                                                                                 *
 * DISABLE_3D_TRYG_CHECK        //Use before 3DTryg.inc for disable Check Plugin Version                                             *
 * DISABLE_3D_TRYG_INIT         //Use before 3DTryg.inc for disable MapAndreas/ColAndreas Auto Init                                  *
 * DISABLE_3D_TRYG_ATM          //Use before 3DTryg.inc for disable ATM Module                                                       *
 * DISABLE_3D_TRYG_ACTOR        //Use before 3DTryg.inc for disable Actors Module                                                    *
 * DISABLE_3D_TRYG_MAPANDREAS   //Use before 3DTryg.inc for disable MapAndreas Module                                                *
 * DISABLE_3D_TRYG_COLANDREAS   //Use before 3DTryg.inc for disable ColAndreas Module                                                *
 * DISABLE_3D_TRYG_YSF          //Use before 3DTryg.inc for disable YSF Module                                                       *
 * DISABLE_3D_TRYG_STREAMER     //Use before 3DTryg.inc for disable Streamer Module                                                  *
 * DISABLE_3D_TRYG_FOXFOREACH   //Use before 3DTryg.inc for disable FoxForeach Module                                                *
 * DISABLE_3D_TRYG_YSIFOREACH   //Use before 3DTryg.inc for disable Foreach Module                                                   *
 * DISABLE_3D_TRYG_FCNPC        //Use before 3DTryg.inc for disable FCNPC Module                                                     *
 * ENABLE_3D_TRYG_TIMELINE_SYNC //Use before 3DTryg.inc for enable Timeline Sync                                                     *
 * ENABLE_3D_TRYG_STREAM3D      //Use before 3DTryg.inc for enable Stream3D Module                                                   *
 * ENABLE_3D_TRYG_LINE3D        //Use before 3DTryg.inc for enable Line3D Module                                                     *
 * ENABLE_3D_TRYG_ANIMS         //Use before 3DTryg.inc for enable Anims Module                                                      *
 *                                                                                                                                   *
 * Complementary Functions:                                                                                                          *
 * Float:sqrtN(Float:value,Float:exponent);                                                                                          *
 * abs(value);                                                                                                                       *
 * Float:fabs(Float:value);                                                                                                          *
 * power(value,Float:exponent);                                                                                                      *
 * IsEven(value);                                                                                                                    *
 * Float:RandomFloat(Float:min,Float:max,accuracy = 4);                                                                              *
 *                                                                                                                                   *
 * Internal Functions:                                                                                                               *
 * single_clock(max,id); //For GetRandomPointOnClock parameter rz                                                                    *
 * even_clock(max,id);   //For GetRandomPointOnClock parameter rz                                                                    *
 * uneven_clock(max,id); //For GetRandomPointOnClock parameter rz                                                                    *
 * NLTZ(value);                           //NotLessThanZero                                                                          *
 * NMTZ(value);                           //NotMoreThanZero                                                                          *
 * Float:NLTZF(Float:value);              //NotLessThanZeroFloat                                                                     *
 * Float:NMTZF(Float:value);              //NotMoreThanZeroFloat                                                                     *
 * NLTV(value,min);                       //NotLessThanValue                                                                         *
 * NMTV(value,max);                       //NotMoreThanValue                                                                         *
 * Float:NLTVF(Float:value,Float:min);    //NotLessThanValueFloat                                                                    *
 * Float:NMTVF(Float:value,Float:max);    //NotMoreThanValueFloat                                                                    *
 * CompRotation(rotation,&crotation=0);   //CompressRotation                                                                         *
 * DeCompRotation(rotation,&crotation=0); //DeCompressRotation                                                                       *
 * Float:CompRotationFloat(Float:rotation,&Float:crotation=0.0);   //CompressRotationFloat                                           *
 * Float:DeCompRotationFloat(Float:rotation,&Float:crotation=0.0); //DeCompressRotationFloat                                         *
 * bool:IsRotationTest(Float:rotation,Float:r_min,Float:r_max);                                                                      *
 * Tryg3D::GivePlayerDamage(targetid,Float:amount,playerid,weaponid,bodypart);                                                       *
 * Tryg3D::GetWeaponDamage(weaponid);                                                                                                *
 * Tryg3D::SwapInt(variable1,variable2);                                                                                             *
 * bool:Tryg3D::IsPlayerSpawned(playerid);                                                                                           *
 * Tryg3D::GetActiveTime();                                                                                                          *
 *                                                                                                                                   *
 * Nero_3D Rotations Functions:                                                                                                      *
 * Tryg3D::GetRotationMatrixEuler(Float:matrix[][],Float:rx,Float:ry,Float:rz,T3D:eulermode:mode=T3D:euler_default);                 *
 * Tryg3D::MatrixRotate(Float:matrix[][],Float:oX,Float:oY,Float:oZ,&Float:x,&Float:y,&Float:z);                                     *
 * Tryg3D::QuatRotate(Float:qw,Float:qx,Float:qy,Float:qz,Float:oX,Float:oY,Float:oZ,&Float:tx,&Float:ty,&Float:tz);                 *
 * Tryg3D::GetQuatFromEuler(Float:rx,Float:ry,Float:rz,&Float:qw,&Float:qx,&Float:qy,&Float:qz,T3D:eulermode:mode=T3D:euler_default);*
 * Tryg3D::EulerRotate(Float:rX,Float:rY,Float:rZ,Float:oX,Float:oY,Float:oZ,&Float:tx,&Float:ty,&Float:tz,                          *
 *                    T3D:eulermode:mode=T3D:euler_default);                                                                         *
 *                                                                                                                                   *
 * General Functions:                                                                                                                *
 * CountPlayers(bool:isplayer=true,bool:isnpc=true);                                                                                 *
 * CountActors();                                                                                                                    *
 * CountVisibleActors(playerid);                                                                                                     *
 * CountVisibleVehicles(playerid);                                                                                                   *
 * CountVisiblePlayers(playerid,bool:isplayer=true,bool:isnpc=true);                                                                 *
 * RecoilFloat(Float:value,Float:recoil);                                                                                            *
 * RecoilVector(&Float:vx,&Float:vy,&Float:vz,Float:sx,Float:sy,Float:sz);                                                           *
 * Float:ShiftDegreeToRadian(Float:deg);                                                                                             *
 * Float:ShiftDegreeToRadianEx(Float:deg);                                                                                           *
 * Float:ShiftDegreeToGrades(Float:deg);                                                                                             *
 * Float:ShiftRadianToDegree(Float:rad);                                                                                             *
 * Float:ShiftRadianToDegreeEx(Float:rad);                                                                                           *
 * Float:ShiftRadianToGrades(Float:rad);                                                                                             *
 * Float:ShiftGradesToDegree(Float:grad);                                                                                            *
 * Float:ShiftGradesToRadian(Float:grad);                                                                                            *
 * GetRandomHit(Float:x,Float:y,Float:z,range,&Float:tx,&Float:ty,&Float:tz);                                                        *
 * Float:GetDistanceBetweenPoints1D(Float:x1,Float:x2);                                                                              *
 * Float:GetDistanceBetweenPoints2D(Float:x1,Float:y1,Float:x2,Float:y2);                                                            *
 * Float:GetDistanceBetweenPoints3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2);                                          *
 * GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty);                                                     *
 * GetPointInFront3D(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);                          *
 * GetPointInFront3DEx(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);               *
 * Float:GetPointInFrontOfPlayer(playerid,&Float:tx,&Float:ty,Float:radius);                                                         *
 * Float:GetPointInFrontOfCamera2D(playerid,&Float:tx,&Float:ty,Float:radius);                                                       *
 * GetPointInFrontOfCamera3D(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0);                       *
 * GetRotationFor2Point2D(Float:x,Float:y,Float:tx,Float:ty,&Float:rz);                                                              *
 * bool:GetRotationFor2Point3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:rx,&Float:rz);                              *
 * ConvertMTARaceRotation(Float:rotation1,Float:rotation2,Float:rotation3,&Float:rx,&Float:ry,&Float:rz);                            *
 * ConvertToMTARaceRotation(Float:rx,Float:ry,Float:rz,&Float:rotation1,&Float:rotation2,&Float:rotation3);                          *
 * GetMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:speed,&rtime=0);                                             *
 * GetSpeedForMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:speed,rtime);                                       *
 * GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz);                                                                      *
 * Float:GetPointInFrontOfVehicle2D(vehicleid,&Float:tx,&Float:ty,Float:radius);                                                     *
 * GetPointInFrontOfVehicle3D(vehicleid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0);                     *
 * GetPlayerCameraRotation(playerid,&Float:rx,&Float:rz);                                                                            *
 * SetPlayerCameraRotation(playerid,Float:rx,Float:rz);                                                                              *
 * Float:GetPlayerCameraZAngle(playerid,&Float:rz=0.0);                                                                              *
 * SetPlayerCameraZAngle(playerid,Float:rz);                                                                                         *
 * GetPointFor2Point2D(Float:x1,Float:y1,Float:x2,Float:y2,Float:percent_size,&Float:tx,&Float:ty);                                  *
 * GetPointFor2Point3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:percent_size,&Float:tx,&Float:ty,&Float:tz);      *
 * GetPointFor2Point2DEx(Float:x1,Float:y1,Float:x2,Float:y2,Float:distance,&Float:tx,&Float:ty);                                    *
 * GetPointFor2Point3DEx(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:distance,&Float:tx,&Float:ty,&Float:tz);        *
 * ShiftVectorToRotation(Float:vx,Float:vy,Float:vz,&Float:rx,&Float:rz);                                                            *
 * ShiftRotationToVector(Float:rx,Float:rz,&Float:vx,&Float:vy,&Float:vz);                                                           *
 * bool:GetPointToPointVector(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:vx,&Float:vy,&Float:vz);                     *
 * Float:GetRandomPointOnClock(Float:x,Float:y,Float:radius,&Float:tx,&Float:ty,&Float:trz,Float:rz = INVALID_ROTATION);             *
 * GetRandomPointInCircle(Float:x,Float:y,Float:radius,&Float:tx,&Float:ty);                                                         *
 * GetRandomPointInCylinder2D(Float:x,Float:y,Float:minz,Float:maxz,Float:radius,&Float:tx,&Float:ty,&Float:tz);                     *
 * GetRandomPointInCylinder3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius,&Float:tx,&Float:ty,&Float:tz);     *
 * GetRandomPointInSphere(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz);                                       *
 * GetRandomPointInRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy,&Float:tx,&Float:ty);                                       *
 * GetRandomPointInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:tx,&Float:ty,&Float:tz);            *
 * GetRandomPointInPolygon(Float:points[],&Float:tx,&Float:ty,maxpoints = sizeof(points));                                           *
 * GetRandomPointInCircularSector(Float:x,Float:y,Float:rz,Float:radius,Float:view_angle,&Float:tx,&Float:ty);                       *
 * GetRandomPointInSphericalSector(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz,                       *
 *                                 &Float:tx,&Float:ty,&Float:tz);                                                                   *
 * GetRandomPointInCone3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius,             *
 *                        &Float:tx,&Float:ty,&Float:tz);                                                                            *
 * GetRandomPointInCube3D(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z,                 *
 *                        &Float:tx,&Float:ty,&Float:tz);                                                                            *
 * GetRandomPointInEllipse(Float:cx,Float:cy,Float:size_x,Float:size_y,&Float:tx,&Float:ty);                                         *
 * GetRandomPointInEllipticalCyl2D(Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y,&Float:tx,&Float:ty,&Float:tz); *
 * GetRandomPointOnCircle(Float:x,Float:y,Float:radius,&Float:tx,&Float:ty);                                                         *
 * GetRandomPointOnCylinder2D(Float:x,Float:y,Float:minz,Float:maxz,Float:radius,&Float:tx,&Float:ty,&Float:tz);                     *
 * GetRandomPointOnCylinder3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius,&Float:tx,&Float:ty,&Float:tz);     *
 * GetRandomPointOnSphere(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz);                                       *
 * GetRandomPointOnRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy,&Float:tx,&Float:ty);                                       *
 * GetRandomPointOnCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:tx,&Float:ty,&Float:tz);            *
 * GetRandomPointOnCircularSector(Float:x,Float:y,Float:rz,Float:radius,Float:view_angle,&Float:tx,&Float:ty);                       *
 * GetRandomPointOnSphericalSector(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz,                       *
 *                                 &Float:tx,&Float:ty,&Float:tz);                                                                   *
 * GetRandomPointOnCone3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius,             *
 *                        &Float:tx,&Float:ty,&Float:tz);                                                                            *
 * GetRandomPointOnCube3D(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z,                 *
 *                        &Float:tx,&Float:ty,&Float:tz);                                                                            *
 * GetRandomPointOnEllipse(Float:cx,Float:cy,Float:size_x,Float:size_y,&Float:tx,&Float:ty);                                         *
 * GetRandomPointOnEllipticalCyl2D(Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y,&Float:tx,&Float:ty,&Float:tz); *
 * bool:IsPointBetween2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB);                                              *
 * bool:IsPointBetween2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB);                   *
 * bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist);                                 *
 * bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist);      *
 * bool:IsPointInCircle(Float:px,Float:py,Float:x,Float:y,Float:radius);                                                             *
 * bool:IsPointInCylinder3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius);          *
 * bool:IsPointInCylinder2D(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:minz,Float:maxz,Float:radius);                          *
 * bool:IsPointInSphere(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:radius);                                            *
 * bool:IsPointInRectangle(Float:x,Float:y,Float:minx,Float:miny,Float:maxx,Float:maxy);                                             *
 * bool:IsPointInCube(Float:x,Float:y,Float:z,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                    *
 * bool:IsPointInPolygon(Float:x,Float:y,Float:points[],maxpoints = sizeof(points));                                                 *
 * bool:IsPointInCircularSector(Float:px,Float:py,Float:x,Float:y,Float:rz,Float:radius,Float:view_angle);                           *
 * bool:IsPointInSphericalSector(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,                  *
 *                               Float:vrx,Float:vrz);                                                                               *
 * bool:IsPointInCone3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,                            *
 *                      Float:pointA_radius,Float:pointB_radius);                                                                    *
 * bool:IsPointInCube3D(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,                               *
 *                      Float:size_x,Float:size_y,Float:size_z);                                                                     *
 * bool:IsPointInEllipse(Float:px,Float:py,Float:cx,Float:cy,Float:size_x,Float:size_y);                                             *
 * bool:IsPointInEllipticalCylinder2D(Float:px,Float:py,Float:pz,Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y); *
 * bool:IsPointInSphericalSectorEx(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,                *
 *                                 Float:vrx,Float:vrz,bool:testLOS=true);                                                           *
 * bool:IsProbable(chance);                                                                                                          *
 * Float:CalculatePercent(Float:value,Float:maxvalue);                                                                               *
 * Float:GetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0);                                                               *
 * Float:SetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0);                                                               *
 * Float:GetPlayerTargetPlayerAngle(playerid,targetid,&Float:rz=0.0);                                                                *
 * Float:SetPlayerTargetPlayerAngle(playerid,targetid,&Float:rz=0.0);                                                                *
 * Float:GetVehicleSpeed(vehicleid);                                                                                                 *
 * Float:GetPlayerSpeed(playerid);                                                                                                   *
 * CreateDynamicExplosion(Float:x,Float:y,Float:z,type,Float:radius,worldid=-1,interiorid=-1,playerid=-1,Float:distance=200.0);      *
 * GetVehicleFlags(vehicleid);                                                                                                       *
 * GetVehicleFlagsByModel(modelid);                                                                                                  *
 * IsVehicleFlag(value,flag);                                                                                                        *
 * GetWeaponShotPos(playerid,hittype,&Float:fx,&Float:fy,&Float:fz);                                                                 *
 * SetPlayerLookAtPlayer(playerid,targetid,cut = CAMERA_CUT);                                                                        *
 * GetPlayerCameraLookAt(playerid,&Float:x,&Float:y,&Float:z);                                                                       *
 * bool:IsPlayerLookAtSky(playerid);                                                                                                 *
 * GetQuatUpVector(Float:qw,Float:qx,Float:qy,Float:qz,&Float:vx,&Float:vy,&Float:vz);                                               *
 * Float:GetLineSize2D(Float:points[][],maxpoints=sizeof(points));                                                                   *
 * Float:GetLineSize3D(Float:points[][],maxpoints=sizeof(points));                                                                   *
 * bool:IsVehicleInRangeOfPoint(vehicleid,Float:range,Float:x,Float:y,Float:z);                                                      *
 * bool:IsActorInRangeOfPoint(actorid,Float:range,Float:x,Float:y,Float:z);                                                          *
 * bool:IsObjectInRangeOfPoint(objectid,Float:range,Float:x,Float:y,Float:z);                                                        *
 * ShiftLineRotation(Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:rx,Float:ry,Float:rz,                               *
 *                   &Float:nX,&Float:nY,&Float:nZ);                                                                                 *
 * ShiftLineRotationVector(Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:rx,Float:ry,Float:rz,                         *
 *                         &Float:nX,&Float:nY,&Float:nZ);                                                                           *
 * Float:GetEllipseRadius(Float:x,Float:y,Float:angle);                                                                              *
 * bool:GetArcPoints3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:ry,                                                  *
 *                     Float:height,Float:points[][],max_points = sizeof(points));                                                   *
 * bool:GetArcPointsFloor3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:spread,Float:points[][],                        *
 *                          max_points = sizeof(points));                                                                            *
 * bool:GetArcPointsCellar3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:spread,Float:points[][],                       *
 *                           max_points = sizeof(points));                                                                           *
 * bool:GetArcPointsLarboard3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:spread,Float:points[][],                     *
 *                             max_points = sizeof(points));                                                                         *
 * bool:GetArcPointsStarboard3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:spread,Float:points[][],                    *
 *                              max_points = sizeof(points));                                                                        *
 * Float:GetDistanceFromPointToLine(Float:px,Float:py,Float:pz,Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,                *
 *                                  &Float:iX=0.0,&Float:iY=0.0,&Float:iZ=0.0);                                                      *
 * ShiftOffsetToPosition(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,                                                         *
 *                       Float:offset_x,Float:offset_y,Float:offset_z,&Float:tx,&Float:ty,&Float:tz);                                *
 * ShiftPositionToOffset(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,                                                         *
 *                       &Float:offset_x,&Float:offset_y,&Float:offset_z,Float:tx,Float:ty,Float:tz);                                *
 * Tryg3D::EulerToQuat(Float:rx,Float:ry,Float:rz,&Float:qw,&Float:qx,&Float:qy,&Float:qz);                                          *
 * Tryg3D::QuatToEuler(&Float:rx,&Float:ry,&Float:rz,Float:qw,Float:qx,Float:qy,Float:qz);                                           *
 * ShiftVectorRotation(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,&Float:tx,&Float:ty,&Float:tz);                            *
 * GetCube3DPoint(OrientationCube3D:orientation,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,                                  *
 *                Float:size_x,Float:size_y,Float:size_z,&Float:tx,&Float:ty,&Float:tz);                                             *
 *                                                                                                                                   *
 * Universal Functions:                                                                                                              *
 * bool:GetElementPos(elementid,Item3D_Type:element_type,&Float:x,&Float:y,&Float:z);                                                *
 * bool:GetElementRotationQuat(elementid,Item3D_Type:element_type,&Float:qw,&Float:qx,&Float:qy,&Float:qz);                          *
 * bool:GetElementUpVector(elementid,Item3D_Type:element_type,&Float:vx,&Float:vy,&Float:vz);                                        *
 * bool:GetElementUpPos(elementid,Item3D_Type:element_type,Float:radius,&Float:x,&Float:y,&Float:z,bool:reverse=false);              *
 * Float:GetElementsDistance(elementid,Item3D_Type:element_type,targetid,Item3D_Type:target_type);                                   *
 * Float:GetElementDistanceFromPoint(elementid,Item3D_Type:element_type,Float:x,Float:y,Float:z);                                    *
 * bool:IsElementOnPlayerScreen(playerid,targetid,Item3D_Type:target_type=item_player,element_orientation:orientation=o_front,       *
 *                              Float:rx=INVALID_ROTATION,Float:rz=INVALID_ROTATION,Float:vrx=VERTICAL_CAMERA_RADIUS,                *
 *                              Float:vrz=HORIZONTAL_CAMERA_RADIUS,bool:testLOS=true,bool:testVW=true);                              *
 * bool:IsElementOnFakeScreen(Float:x,Float:y,Float:z,targetid,Item3D_Type:target_type,Float:rx,Float:rz,                            *
 *                            Float:vrx=VERTICAL_CAMERA_RADIUS,Float:vrz=HORIZONTAL_CAMERA_RADIUS,bool:testLOS=true);                *
 * bool:IsElementInCircle(elementid,Item3D_Type:element_type,Float:x,Float:y,Float:radius);                                          *
 * bool:IsElementInCylinder3D(elementid,Item3D_Type:element_type,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,              *
 *                            Float:radius);                                                                                         *
 * bool:IsElementInCylinder2D(elementid,Item3D_Type:element_type,Float:x,Float:y,Float:minz,Float:maxz,Float:radius);                *
 * bool:IsElementInSphere(elementid,Item3D_Type:element_type,Float:x,Float:y,Float:z,Float:radius);                                  *
 * bool:IsElementInRectangle(elementid,Item3D_Type:element_type,Float:minx,Float:miny,Float:maxx,Float:maxy);                        *
 * bool:IsElementInCube(elementid,Item3D_Type:element_type,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);       *
 * bool:IsElementInPolygon(elementid,Item3D_Type:element_type,Float:points[],maxpoints = sizeof(points));                            *
 * bool:IsElementInCircularSector(elementid,Item3D_Type:element_type,Float:x,Float:y,Float:rz,Float:radius,Float:view_angle);        *
 * bool:IsElementInSphericalSector(elementid,Item3D_Type:element_type,Float:x,Float:y,Float:z,Float:rx,Float:rz,                     *
 *                                 Float:radius,Float:vrx,Float:vrz);                                                                *
 * bool:IsElementInCone(elementid,Item3D_Type:element_type,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,                    *
 *                      Float:pointA_radius,Float:pointB_radius);                                                                    *
 * bool:IsElementInCube3D(elementid,Item3D_Type:element_type,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,                     *
 *                        Float:size_x,Float:size_y,Float:size_z);                                                                   *
 * GetElementToPointVector(elementid,Item3D_Type:element_type,Float:tx,Float:ty,Float:tz,&Float:vx,&Float:vy,&Float:vz);             *
 * bool:GetElementRotatedVector(elementid,Item3D_Type:element_type,Float:tx,Float:ty,Float:tz,                                       *
 *                              &Float:vx,&Float:vy,&Float:vz,bool:return_vector=true,Float:rx=0.0,Float:ry=0.0,Float:rz=0.0);       *
 * bool:GetElementOrientationPos(elementid,Item3D_Type:element_type,element_orientation:orientation,Float:distance,                  *
 *                               &Float:tx,&Float:ty,&Float:tz);                                                                     *
 * bool:IsElementInEllipse(elementid,Item3D_Type:element_type,Float:cx,Float:cy,Float:size_x,Float:size_y);                          *
 * bool:IsElementInEllipticalCylinder2D(elementid,Item3D_Type:element_type,Float:cx,Float:cy,Float:minz,Float:maxz,                  *
 *                                      Float:size_x,Float:size_y);                                                                  *
 *                                                                                                                                   *
 * Universal Functions (ColAndreas):                                                                                                 *
 * bool:IsBetweenElementsIsWall(elementid,Item3D_Type:element_type,targetid,Item3D_Type:target_type);                                *
 * bool:IsBetweenElementToPointIsWall(Float:x,Float:y,Float:z,targetid,Item3D_Type:target_type);                                     *
 * GetElementCollisionFlags(elementid,Item3D_Type:element_type);                                                                     *
 * bool:IsPlayerInRangeOfElement(playerid,Float:range,targetid,Item3D_Type:target_type=item_player,bool:testLOS=true);               *
 * bool:IsElementInRangeOfPoint(Float:x,Float:y,Float:z,Float:range,targetid,Item3D_Type:target_type=item_player,                    *
 *                              bool:testLOS=true);                                                                                  *
 * bool:IsElementInRangeOfElement(elementid,Item3D_Type:element_type,Float:range,targetid,Item3D_Type:target_type=item_player,       *
 *                                bool:testLOS=true);                                                                                *
 * bool:GetElementOrientationPosCol(elementid,Item3D_Type:element_type,element_orientation:orientation,Float:distance,               *
 *                                  &Float:tx,&Float:ty,&Float:tz);                                                                  *
 * bool:IsPointInWaterOrientOfElement(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:radius,                            *
 *                                    element_orientation:orientation=o_front);                                                      *
 * GetVehiclePartPos(vehicleid,partid,&Float:tx,&Float:ty,&Float:tz,Float:offset_x=0.0,Float:offset_y=0.0,Float:offset_z=0.0);       *
 *                                                                                                                                   *
 * Universal Functions (Stream3D):                                                                                                   *
 * bool:IsElementInStream(elementid,Item3D_Type:element_type,Stream:StreamData[Stream3D]);                                           *
 *                                                                                                                                   *
 * Extended Functions:                                                                                                               *
 * Tryg3D::GetModules(&modules_count=0);                                                                                             *
 * bool:Tryg3D::IsModuleLoaded(Tryg3DModule:moduleid);                                                                               *
 * Tryg3D::GetEfficiency(bool:use_colandreas=false);                                                                                 *
 * Tryg3D::GetErrorCount();                                                                                                          *
 * Tryg3D::ResetErrorCount();                                                                                                        *
 * Tryg3D::SetStreamDistance(Float:streamdistance); //default 300.0                                                                  *
 * Float:Tryg3D::GetStreamDistance();                                                                                                *
 * Tryg3D::GetActiveCount();                                                                                                         *
 *                                                                                                                                   *
 * Animation Functions:                                                                                                              *
 * bool:IsPlayerSkydiving(playerid);      //Animation Test                                                                           *
 * bool:IsPlayerUsingParachute(playerid); //Animation Test                                                                           *
 * bool:IsPlayerAiming(playerid);         //Animation Test                                                                           *
 * bool:IsPlayerStay(playerid);           //Animation Test                                                                           *
 * bool:IsPlayerRunning(playerid);        //Animation Test                                                                           *
 * bool:IsPlayerSwim(playerid);           //Animation Test                                                                           *
 * bool:IsPlayerJump(playerid);           //Animation Test                                                                           *
 * bool:IsPlayerParaFall(playerid);       //Animation Test                                                                           *
 * bool:IsPlayerParaGlide(playerid);      //Animation Test                                                                           *
 * bool:IsPlayerFall(playerid);           //Animation Test                                                                           *
 *                                                                                                                                   *
 * ATM Module Functions:                                                                                                             *
 * randomex(min,max);                                                                                                                *
 * Tryg3D::KeyPressed(key);                                                                                                          *
 * Tryg3D::KeyReleased(key);                                                                                                         *
 * Tryg3D::KeyHolding(key);                                                                                                          *
 * Tryg3D::GetSAMIncludeVersion(value,name[],maxdest = sizeof(name));                                                                *
 * Tryg3D::DisableADMLogging(bool:disable);                                                                                          *
 * Tryg3D::SecToTimeDay(second);      //Use: %d:%02d:%02d:%02d                                                                       *
 * Tryg3D::MSToTimeDay(millisecond);  //Use: %d:%02d:%02d:%02d                                                                       *
 * Tryg3D::SecToTime(second);         //Use: %02d:%02d:%02d                                                                          *
 * Tryg3D::MSToTime(millisecond);     //Use: %02d:%02d:%02d                                                                          *
 * Tryg3D::SecToTimeMini(second);     //Use: %02d:%02d                                                                               *
 * Tryg3D::MSToTimeMini(millisecond); //Use: %02d:%02d                                                                               *
 *                                                                                                                                   *
 * Streamer Functions:                                                                                                               *
 * bool:IsDynamicObjectInRangeOfPoint(objectid,Float:range,Float:x,Float:y,Float:z);                                                 *
 * SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid = -1,interiorid = -1,compensatedtime = -1,         *
 *                           freezeplayer = 1);                                                                                      *
 * SetPlayerAbsolutePositionVeh(playerid,Float:x,Float:y,Float:z,Float:angle,worldid = -1,interiorid = -1,compensatedtime = -1,      *
 *                              freezeplayer = 1);                                                                                   *
 * bool:IsDynamicActorInRangeOfPoint(actorid,Float:range,Float:x,Float:y,Float:z);                                                   *
 * bool:IsVehicleFullyInDynamicArea(vehicleid,areaid);                                                                               *
 * bool:GetRandomPointInDynamicArea(STREAMER_TAG_AREA areaid,&Float:tx,&Float:ty,&Float:tz);                                         *
 *                                                                                                                                   *
 * Streamer Extended Functions:                                                                                                      *
 * bool:Tryg3D::IsValidStreamer(version);                                                                                            *
 * Tryg3D::GetStreamerVersionName(name[],value = TRYG3D_GET_STREAMER_VERSION,maxdest = sizeof(name));                                *
 * Tryg3D::CheckStreamerVersion();                                                                                                   *
 *                                                                                                                                   *
 * Streamer Functions (FCNPC):                                                                                                       *
 * SetNPCAbsolutePosition(npcid,Float:x,Float:y,Float:z,Float:angle,worldid = -1,interiorid = -1,compensatedtime = -1,               *
 *                        freezeplayer = 1);                                                                                         *
 *                                                                                                                                   *
 * MapAndreas Functions:                                                                                                             *
 * Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0);                                                                              *
 * GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry);                                                                *
 * GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance);              *
 * bool:IsPointInWater(Float:x,Float:y,Float:z=0.0);                                                                                 *
 *                                                                                                                                   *
 * MapAndreas Extended Functions:                                                                                                    *
 * bool:IsMapAndreasInit();                                                                                                          *
 * SafeMapAndreasInit(mode = MAP_ANDREAS_MODE_FULL, name[]="", len=sizeof(name));                                                    *
 *                                                                                                                                   *
 * ColAndreas Functions:                                                                                                             *
 * MovePointCol(Float:StartX,Float:StartY,Float:StartZ,Float:EndX,Float:EndY,Float:EndZ,&Float:x,&Float:y,&Float:z);                 *
 * bool:MovePointColCutLine(Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,&Float:x,&Float:y,&Float:z,Float:cut_size=0.0);    *
 * bool:MovePointColCutLineEx(Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,&Float:x,&Float:y,&Float:z,Float:cut_size=0.0);  *
 * GetPointInFront3DCol(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);                       *
 * GetPointInFront3DColEx(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz);            *
 * Float:GetPointInFrontOfPlayerCol(playerid,&Float:tx,&Float:ty,Float:radius);                                                      *
 * Float:GetPointInFrontOfCamera2DCol(playerid,&Float:tx,&Float:ty,Float:radius);                                                    *
 * GetPointInFrontOfCamera3DCol(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0);                    *
 * Float:GetPointInFrontOfVehicle2DCol(vehicleid,&Float:tx,&Float:ty,Float:radius);                                                  *
 * GetPointInFrontOfVehicle3DCol(vehicleid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0);                  *
 * GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry);                                                                *
 * GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance);              *
 * GetPointCollisionFlags(Float:x,Float:y,Float:z,interiorid=0);                                                                     *
 * IsCollisionFlag(value,flag);                                                                                                      *
 * Float:UndergroundFindZ(Float:x,Float:y,&Float:z=0.0);                                                                             *
 * Float:InteriorFindZ(Float:px,Float:py,Float:pz=1000.0,Float:size=2.0,&Float:z=0.0);                                               *
 * bool:IsPointInWater(Float:x,Float:y,Float:z=0.0);                                                                                 *
 * bool:IsPointInUnderwater(Float:x,Float:y,Float:z);                                                                                *
 * bool:IsPointInUnderground(Float:x,Float:y,Float:z);                                                                               *
 * bool:IsPointInAir(Float:x,Float:y,Float:z,bool:interior=false,Float:max_distance=2.2);                                            *
 * bool:IsPointInGround(Float:x,Float:y,Float:z,bool:interior=false,Float:max_distance=2.2);                                         *
 * bool:IsBetweenPlayersIsWall(playerid,targetid);                                                                                   *
 * bool:IsBetweenPlayerToPointIsWall(playerid,Float:x,Float:y,Float:z);                                                              *
 * bool:GetPointInWallForPoint(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,Float:sector=90.0);                *
 * bool:GetWallRotation(Float:sx,Float:sy,Float:sz,Float:ex,Float:ey,Float:ez,&Float:rx,&Float:rz,                                   *
 *                      &Float:px=0.0,&Float:py=0.0,&Float:pz=0.0,Float:size=1.0,Float:cut_size=0.0);                                *
 * Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0);                                                                              *
 *                                                                                                                                   *
 * ColAndreas Extended Functions:                                                                                                    *
 * bool:IsColAndreasInit();                                                                                                          *
 * SafeColAndreasInit();                                                                                                             *
 * GetColAndreasVersion();                                                                                                           *
 * GetValidColAndreasVersion();                                                                                                      *
 * bool:IsValidColAndreas(version);                                                                                                  *
 * GetColAndreasVersionName(name[],value = GET_COLANDREAS_VERSION,maxdest = sizeof(name));                                           *
 * CheckColAndreasVersion();                                                                                                         *
 *                                                                                                                                   *
 * ColAndreas Callbacks:                                                                                                             *
 * OnColAndreasRemoveBuilding();                                                                                                     *
 *                                                                                                                                   *
 * YSF Functions:                                                                                                                    *
 * Float:GetPlayerHydraReactorRX(playerid);                                                                                          *
 * bool:IsPlayerHydraReactorBoost(playerid);                                                                                         *
 * GetPlayerRotation(playerid,&Float:rx,&Float:ry,&Float:rz);                                                                        *
 * CountTextDraw();                                                                                                                  *
 * CountPlayerTextDraw(playerid);                                                                                                    *
 * CountVisibleTextDraw(playerid);                                                                                                   *
 * CountVisiblePlayerTextDraw(playerid);                                                                                             *
 * CountGangZone();                                                                                                                  *
 * CountVisibleGangZone(playerid);                                                                                                   *
 * CountPlayerGangZone(playerid);                                                                                                    *
 * CountVisiblePlayerGangZone(playerid);                                                                                             *
 * bool:IsVehicleOnSpawn(vehicleid,Float:check_radius=1.0);                                                                          *
 * bool:IsPlayerOnSpawn(playerid,Float:check_radius=1.0);                                                                            *
 * GetRandomPointInGangZone(zoneid,&Float:tx,&Float:ty);                                                                             *
 * GetRandomPointInPlayerGangZone(playerid,zoneid,&Float:tx,&Float:ty);                                                              *
 *                                                                                                                                   *
 * YSF Functions (TimeLine):                                                                                                         *
 * UpdatePlayerTimeline(playerid);                                                                                                   *
 * GetPlayerTimeline(playerid);                                                                                                      *
 * SetPlayerTimeline(playerid,timeline);                                                                                             *
 * GetPlayerPos4D(playerid,&Float:x,&Float:y,&Float:z,&timeline);                                                                    *
 * SetPlayerPos4D(playerid,Float:x,Float:y,Float:z,timeline=0);                                                                      *
 * CreateDynamicExplosion4D(Float:x,Float:y,Float:z,type,Float:radius,worldid = -1,interiorid = -1,timeline = -1,playerid = -1,      *
 *                          Float:distance = 200.0);                                                                                 *
 * TogglePlayerVisibleOnServer(playerid,bool:toggle);                                                                                *
 * bool:IsPlayerVisibleOnServer(playerid);                                                                                           *
 *                                                                                                                                   *
 * YSF Extended Functions (TimeLine):                                                                                                *
 * UpdatePlayerOnServer(playerid); //Performed automatically                                                                         *
 * CheckPlayersOnServer(playerid); //Performed automatically                                                                         *
 *                                                                                                                                   *
 * FCNPC Functions:                                                                                                                  *
 * Float:GetPointInFrontOfNPC(npcid,&Float:tx,&Float:ty,Float:radius);                                                               *
 * bool:IsNPCInRangeOfPoint(npcid,Float:range,Float:x,Float:y,Float:z);                                                              *
 * Float:GetNPCSpeed(npcid);                                                                                                         *
 * Float:GetNPCTargetAngle(npcid,Float:x,Float:y,&Float:rz=0.0);                                                                     *
 * Float:SetNPCTargetAngle(npcid,Float:x,Float:y,&Float:rz=0.0);                                                                     *
 * Float:GetNPCTargetNPCAngle(npcid,targetid,&Float:rz=0.0);                                                                         *
 * Float:SetNPCTargetNPCAngle(npcid,targetid,&Float:rz=0.0);                                                                         *
 * FCNPC_SetVehicleRotation(npcid,Float:rx,Float:ry,Float:rz);                                                                       *
 * bool:FCNPC_SetVehicleTargetRotation(npcid,Float:tx,Float:ty,Float:tz,Float:ry=0.0);                                               *
 * FCNPC_GoToAir(npcid,Float:x,Float:y,Float:z,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO);                                 *
 *                                                                                                                                   *
 * FCNPC Functions (ColAndreas):                                                                                                     *
 * Float:GetPointInFrontOfNPCCol(npcid,&Float:tx,&Float:ty,Float:radius);                                                            *
 * FCNPC_GoToCol(npcid,Float:x,Float:y,Float:z,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,       *
 *               Float:cut_size = 0.0,bool:setangle = true);                                                                         *
 * FCNPC_GoToPlayerCol(npcid,playerid,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,                *
 *                     Float:cut_size = 0.0,bool:setangle = true);                                                                   *
 * FCNPC_GoToPlayerOnGroundCol(npcid,playerid,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,        *
 *                             Float:cut_size = 1.0,Float:climbing = 2.0,bool:setangle = true);                                      *
 * FCNPC_GoToAirCol(npcid,Float:x,Float:y,Float:z,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,Float:cut_size = 0.0);         *
 * FCNPC_RandomMoveInDynamicArea(npcid,STREAMER_TAG_AREA areaid,Float:climbing = 2.0,type = MOVE_TYPE_AUTO,                          *
 *                               Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,bool:setangle = true);                     *
 * FCNPC_RandomMoveInStream(npcid,Stream:StreamData[Stream3D],Float:climbing = 2.0,type = MOVE_TYPE_AUTO,                            *
 *                          Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,bool:setangle = true);                          *
 *                                                                                                                                   *
 * Stream3D Functions:                                                                                                               *
 * StreamCreate(variable);                                                                                                           *
 * StreamType:GetStreamType(Stream:StreamData[Stream3D]);                                                                            *
 * Stream:ConvertAreaToStream(areaid);                                                                                               *
 * Stream:StreamCircle(Float:x,Float:y,Float:radius);                                                                                *
 * Stream:StreamCylinder3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius);                                      *
 * Stream:StreamCylinder2D(Float:x,Float:y,Float:minz,Float:maxz,Float:radius);                                                      *
 * Stream:StreamSphere(Float:x,Float:y,Float:z,Float:radius);                                                                        *
 * Stream:StreamRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy);                                                              *
 * Stream:StreamCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                                             *
 * Stream:StreamCircularSector(Float:x,Float:y,Float:rz,Float:radius,Float:view_angle);                                              *
 * Stream:StreamSphericalSector(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz);                         *
 * Stream:StreamCone3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius);               *
 * Stream:StreamCube3D(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z);                   *
 * Stream:StreamEllipse(Float:cx,Float:cy,Float:size_x,Float:size_y);                                                                *
 * Stream:StreamEllipticalCylinder2D(Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y);                             *
 * bool:IsValidStream(Stream:StreamData[Stream3D]);                                                                                  *
 * bool:IsPointInStream(Float:x,Float:y,Float:z,Stream:StreamData[Stream3D]);                                                        *
 * bool:GetRandomPointInStream(Stream:StreamData[Stream3D],&Float:x,&Float:y,&Float:z);                                              *
 * bool:GetRandomPointOnStream(Stream:StreamData[Stream3D],&Float:x,&Float:y,&Float:z);                                              *
 * bool:IsVehicleFullyInStream(vehicleid,Stream:StreamData[Stream3D]);                                                               *
 *                                                                                                                                   *
 * Line3D Functions:                                                                                                                 *
 * Line3DCreate(variable,max_points);                                                                                                *
 * GetLine3DValue(variable,pointid,name);                                                                                            *
 * SetLine3DValue(variable,pointid,name,value);                                                                                      *
 * bool:GetLine3DPointPos(Line3D:LineData[][LinePoint3D],pointid,&Float:x,&Float:y,&Float:z,max_points = sizeof(LineData));          *
 * bool:SetLine3DPointPos(Line3D:LineData[][LinePoint3D],pointid,Float:x,Float:y,Float:z,max_points = sizeof(LineData));             *
 * bool:GetLine3DPointRot(Line3D:LineData[][LinePoint3D],pointid,&Float:rx,&Float:ry,&Float:rz,max_points = sizeof(LineData));       *
 * bool:SetLine3DPointRot(Line3D:LineData[][LinePoint3D],pointid,Float:rx,Float:ry,Float:rz,max_points = sizeof(LineData));          *
 * CountLine3DPoints(Line3D:LineData[][LinePoint3D],max_points = sizeof(LineData));                                                  *
 * AddPointToLine3D(Line3D:LineData[][LinePoint3D],Float:x,Float:y,Float:z,Float:rx=INVALID_ROTATION,                                *
 *                  Float:ry=INVALID_ROTATION,Float:rz=INVALID_ROTATION,max_points = sizeof(LineData));                              *
 *                                                                                                                                   *
 * Deprecated Functions:                                                                                                             *
 * Float:GetActorDistanceFromPoint(actorid,Float:x,Float:y,Float:z);                                                                 *
 * Float:GetObjectDistanceFromPoint(objectid,Float:x,Float:y,Float:z);                                                               *
 * Float:GetDistanceBetweenPlayers(playerid_a,playerid_b);                                                                           *
 * Float:GetDistanceBetweenVehicles(vehicleid_a,vehicleid_b);                                                                        *
 * Float:GetDistanceBetweenObjects(objectid_a,objectid_b);                                                                           *
 * Float:GetPlayerActorDistance(playerid,actorid);                                                                                   *
 * Float:GetPlayerVehicleDistance(playerid,vehicleid);                                                                               *
 * Float:GetPlayerObjectDistance(playerid,objectid);                                                                                 *
 * bool:IsPlayerInCircle(playerid,Float:x,Float:y,Float:radius);                                                                     *
 * bool:IsPlayerInCylinder3D(playerid,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius);                           *
 * bool:IsPlayerInCylinder2D(playerid,Float:x,Float:y,Float:minz,Float:maxz,Float:radius);                                           *
 * bool:IsPlayerInSphere(playerid,Float:x,Float:y,Float:z,Float:radius);                                                             *
 * bool:IsPlayerInRectangle(playerid,Float:minx,Float:miny,Float:maxx,Float:maxy);                                                   *
 * bool:IsPlayerInCube(playerid,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz);                                  *
 * bool:IsPlayerInPolygon(playerid,Float:points[],maxpoints = sizeof(points));                                                       *
 * bool:IsPlayerInCircularSector(playerid,Float:x,Float:y,Float:rz,Float:radius,Float:view_angle);                                   *
 * bool:IsPlayerInSphericalSector(playerid,Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz);              *
 * bool:IsPlayerInCone(playerid,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius);      *
 * bool:IsPlayerInCube3D(playerid,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z);        *
 * bool:IsPlayerInEllipse(playerid,Float:cx,Float:cy,Float:size_x,Float:size_y);                                                     *
 * bool:IsPlayerInEllipticalCylinder2D(playerid,Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y);                  *
 * GetPlayerCollisionFlags(playerid);                                                                                                *
 * GetVehicleCollisionFlags(vehicleid);                                                                                              *
 * bool:IsPointInWaterFrontOfPlayer(playerid,Float:radius);                                                                          *
 *                                                                                                                                   *
 * Symbols:                                                                                                                          *
 * FLOAT_PI                   - pi constant value                                                                                    *
 * FLOAT_EULER                - Euler number                                                                                         *
 * FLOAT_NAN                  - Float NaN                                                                                            *
 * FLOAT_DEFECT               - Float defect (Arc Test)                                                                              *
 * FLOAT_INFINITY             - Float Infinity                                                                                       *
 * VBTP                       - Value Bigger Than Possible                                                                           *
 * VLTP                       - Value Lower Than Possible                                                                            *
 *                                                                                                                                   *
 * Definitions:                                                                                                                      *
 * VERTICAL_CAMERA_RADIUS     - (modifiable)                                                                                         *
 * HORIZONTAL_CAMERA_RADIUS   - (modifiable)                                                                                         *
 * INVALID_ROTATION           - (modifiable)                                                                                         *
 * MAX_POLYGON_POINTS         - (modifiable)                                                                                         *
 * VEHICLE_SPEED_MULTIPLIER   - (modifiable)                                                                                         *
 * PLAYER_SPEED_MULTIPLIER    - (modifiable)                                                                                         *
 * INVALID_MOVE_TIME          - (modifiable)                                                                                         *
 * INVALID_MOVE_SPEED         - (modifiable)                                                                                         *
 * INVALID_LINE3D_POINT_ID                                                                                                           *
 *                                                                                                                                   *
 * Module ID:                                                                                                                        *
 * TRYG3D_MODULEID_MAPANDREAS - MapAndreas Plugin Module ID                                                                          *
 * TRYG3D_MODULEID_COLANDREAS - ColAndreas Plugin Module ID                                                                          *
 * TRYG3D_MODULEID_YSF        - YSF Plugin Module ID                                                                                 *
 * TRYG3D_MODULEID_STREAMER   - Streamer Plugin Module ID                                                                            *
 * TRYG3D_MODULEID_FOXFOREACH - FoxForeach Include Module ID                                                                         *
 * TRYG3D_MODULEID_YSIFOREACH - YSIForeach Include Module ID                                                                         *
 * TRYG3D_MODULEID_FCNPC      - FCNPC Plugin Module ID                                                                               *
 * TRYG3D_MODULEID_STREAM3D   - Stream3D Module ID                                                                                   *
 * TRYG3D_MODULEID_LINE3D     - Line3D Module ID                                                                                     *
 *                                                                                                                                   *
 * Position Flags:                                                                                                                   *
 * POSITION_FLAG_WORLD                                                                                                               *
 * POSITION_FLAG_INTERIOR                                                                                                            *
 * POSITION_FLAG_AIR                                                                                                                 *
 * POSITION_FLAG_GROUND                                                                                                              *
 * POSITION_FLAG_WATER                                                                                                               *
 * POSITION_FLAG_UNDERWATER                                                                                                          *
 * POSITION_FLAG_UNDERGROUND                                                                                                         *
 *                                                                                                                                   *
 * Vehicle Flags:                                                                                                                    *
 * VF_STREET        VF_AIRBORNE      VF_NATATORIAL    VF_MILITARY      VF_TRAIN         VF_RC            VF_CARRIAGE                 *
 * VF_AIRPLANE      VF_HELICOPTER    VF_BIKES         VF_TRAILER       VF_TOWABLE       VF_POLICE                                    *
 *                                                                                                                                   *
 * Vehicle Parts:                                                                                                                    *
 * VEHICLE_PART_RFTIRE        - Right Front tire                                                                                     *
 * VEHICLE_PART_LFTIRE        - Left Front tire                                                                                      *
 * VEHICLE_PART_RRTIRE        - Right Rear tire                                                                                      *
 * VEHICLE_PART_LRTIRE        - Left Rear tire                                                                                       *
 * VEHICLE_PART_HOOD          - In Front                                                                                             *
 * VEHICLE_PART_TRUNK         - Behind                                                                                               *
 * VEHICLE_PART_ROOF          - Roof                                                                                                 *
 * VEHICLE_PART_CHASSIS       - Chassis                                                                                              *
 * VEHICLE_PART_PETROLCAP     - Petrolcap                                                                                            *
 *                                                                                                                                   *
 * enum 'element_orientation'                                                                                                        *
 * # o_left                   - Orientation Left                                                                                     *
 * # o_right                  - Orientation Right                                                                                    *
 * # o_up                     - Orientation UP                                                                                       *
 * # o_down                   - Orientation Down                                                                                     *
 * # o_front                  - Orientation Front                                                                                    *
 * # o_back                   - Orientation Back                                                                                     *
 *                                                                                                                                   *
 * enum 'Item3D_Type'                                                                                                                *
 * # item_player                                                                                                                     *
 * # item_npc                                                                                                                        *
 * # item_actor                                                                                                                      *
 * # item_object                                                                                                                     *
 * # item_vehicle                                                                                                                    *
 * # item_dynamic_object                                                                                                             *
 * # item_dynamic_pickup                                                                                                             *
 * # item_dynamic_cp                                                                                                                 *
 * # item_dynamic_racecp                                                                                                             *
 * # item_dynamic_mapicon                                                                                                            *
 * # item_dynamic_3dtext                                                                                                             *
 * # item_dynamic_actor                                                                                                              *
 *                                                                                                                                   *
 * enum 'Vectors3D'                                                                                                                  *
 * # Float: T3D:X             - Position X                                                                                           *
 * # Float: T3D:Y             - Position Y                                                                                           *
 * # Float: T3D:Z             - Position Z                                                                                           *
 * # Float: T3D:A             - Angle                                                                                                *
 *                                                                                                                                   *
 * enum 'Orions3D'                                                                                                                   *
 * # Float: T3D:orion         - First orion value                                                                                    *
 * # Float: T3D:lon           - Second orion value                                                                                   *
 * # Float: T3D:lat           - Third orion value                                                                                    *
 *                                                                                                                                   *
 * enum 'Float3D'                                                                                                                    *
 * # Float: T3D:X             - Position X                                                                                           *
 * # Float: T3D:Y             - Position Y                                                                                           *
 * # Float: T3D:Z             - Position Z                                                                                           *
 * # Float: T3D:rX            - Rotation X                                                                                           *
 * # Float: T3D:rY            - Rotation Y                                                                                           *
 * # Float: T3D:rZ            - Rotation Z                                                                                           *
 * # Float: T3D:tX            - Target Position X                                                                                    *
 * # Float: T3D:tY            - Target Position Y                                                                                    *
 * # Float: T3D:tZ            - Target Position Z                                                                                    *
 * #        T3D:VW            - Virtual World ID                                                                                     *
 * #        T3D:INT           - Interior ID                                                                                          *
 * # Float: T3D:SPEED         - Speed                                                                                                *
 *                                                                                                                                   *
 * enum 'LongFloat3D'                                                                                                                *
 * # Float: T3D:X             - Position X                                                                                           *
 * # Float: T3D:Y             - Position Y                                                                                           *
 * # Float: T3D:Z             - Position Z                                                                                           *
 * # Float: T3D:rX            - Rotation X                                                                                           *
 * # Float: T3D:rY            - Rotation Y                                                                                           *
 * # Float: T3D:rZ            - Rotation Z                                                                                           *
 * # Float: T3D:tX            - Target Position X                                                                                    *
 * # Float: T3D:tY            - Target Position Y                                                                                    *
 * # Float: T3D:tZ            - Target Position Z                                                                                    *
 * # Float: T3D:trX           - Target Rotation X                                                                                    *
 * # Float: T3D:trY           - Target Rotation Y                                                                                    *
 * # Float: T3D:trZ           - Target Rotation Z                                                                                    *
 * # Float: T3D:VecX          - Vector Position X                                                                                    *
 * # Float: T3D:VecY          - Vector Position Y                                                                                    *
 * # Float: T3D:VecZ          - Vector Position Z                                                                                    *
 * #        T3D:VW            - Virtual World ID                                                                                     *
 * #        T3D:INT           - Interior ID                                                                                          *
 * # Float: T3D:SPEED         - Speed                                                                                                *
 *                                                                                                                                   *
 * enum 'StreamType'                                                                                                                 *
 * # s_invalid                                                                                                                       *
 * # s_circle                                                                                                                        *
 * # s_cylinder2d                                                                                                                    *
 * # s_cylinder3d                                                                                                                    *
 * # s_sphere                                                                                                                        *
 * # s_rectangle                                                                                                                     *
 * # s_cube2d                                                                                                                        *
 * # s_cube3d                                                                                                                        *
 * # s_circularsector                                                                                                                *
 * # s_sphericalsector                                                                                                               *
 * # s_cone                                                                                                                          *
 * # s_ellipse                                                                                                                       *
 * # s_ellipticalcyl2d                                                                                                               *
 *                                                                                                                                   *
 * enum 'OrientationCube3D'                                                                                                          *
 * # o_left_back_down                                                                                                                *
 * # o_right_back_down                                                                                                               *
 * # o_right_front_down                                                                                                              *
 * # o_left_front_down                                                                                                               *
 * # o_left_back_up                                                                                                                  *
 * # o_right_back_up                                                                                                                 *
 * # o_right_front_up                                                                                                                *
 * # o_left_front_up                                                                                                                 *
 *                                                                                                                                   *
 * enum 'LinePoint3D'                                                                                                                *
 * # bool:  T3D:PointUsed     - Is point used                                                                                        *
 * # Float: T3D:X             - Position X                                                                                           *
 * # Float: T3D:Y             - Position Y                                                                                           *
 * # Float: T3D:Z             - Position Z                                                                                           *
 * # Float: T3D:rX            - Rotation X                                                                                           *
 * # Float: T3D:rY            - Rotation Y                                                                                           *
 * # Float: T3D:rZ            - Rotation Z                                                                                           *
 *                                                                                                                                   *
 * Functions extra names:                                                                                                            *
 * GetDistanceBetweenPoints   -> GetDistanceBetweenPoints3D                                                                          *
 * Tryg3D::MapAndreasFindZ     -> CA_FindZ_For2DCoord / MapAndreasFindZ                                                              *
 * GetPlayersDistance         -> GetDistanceBetweenPlayers                                                                           *
 * GetVehiclesDistance        -> GetDistanceBetweenVehicles                                                                          *
 * GetObjectsDistance         -> GetDistanceBetweenObjects                                                                           *
 *                                                                                                                                   *
 *************************************************************************************************************************************/

/*
//Check Version 3DTryg.inc
#if !defined _3D_Tryg
	#error [ADM] You need 3DTryg.inc v4.2.0
#elseif !defined Tryg3D_Version
	#error [ADM] Update you 3DTryg.inc to v4.2.0
#elseif (Tryg3D_Version < 40200)
	#error [ADM] Update you 3DTryg.inc to v4.2.0
#endif
*/
 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Version                                                                                                                          *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
 
#if defined _3D_Tryg
	#endinput
#endif
#define _3D_Tryg

#define Tryg3D_Version									(40200) //a.b.c 10000*a+100*b+c
#define Tryg3D_SAMP_Version								"0.3.7"

#if (!defined GetPlayerPoolSize)
	#error [ADM] This include requires SA:MP version 0.3.7
#endif

#if defined _Text_Draw_Ex
	#error [ADM] Please remove deprecated file TextDrawEx.inc
#endif

#if defined _Map_Andreas_Ex
	#error [ADM] Please remove deprecated file MapAndreasEx.inc
#endif

//Update Checker
#if !defined HTTP
	#tryinclude <a_http>
#endif

#if !defined HTTP
	#tryinclude "a_http"
#endif

#if !defined HTTP
	#error [ADM] Please include a_http.inc before 3DTryg.inc
#endif

 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Modules                                                                                                                          *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

//Tryg3D Plugin Module List
#define TRYG3D_MODULEID_MAPANDREAS						(Tryg3DModule:0b0000000000000001)
#define TRYG3D_MODULEID_COLANDREAS						(Tryg3DModule:0b0000000000000010)
#define TRYG3D_MODULEID_YSF								(Tryg3DModule:0b0000000000000100)
#define TRYG3D_MODULEID_STREAMER						(Tryg3DModule:0b0000000000001000)
#define TRYG3D_MODULEID_FOXFOREACH						(Tryg3DModule:0b0000000000010000)
#define TRYG3D_MODULEID_YSIFOREACH						(Tryg3DModule:0b0000000000100000)
#define TRYG3D_MODULEID_FCNPC							(Tryg3DModule:0b0000000001000000)
#define TRYG3D_MODULEID_STREAM3D						(Tryg3DModule:0b0000000010000000)
#define TRYG3D_MODULEID_LINE3D							(Tryg3DModule:0b0000000100000000)
#define TRYG3D_MODULEID_ACTOR 							(Tryg3DModule:0b0000001000000000)
#define TRYG3D_MODULEID_ATM   							(Tryg3DModule:0b0000010000000000)
#define TRYG3D_MODULEID_ANIMS 							(Tryg3DModule:0b0000100000000000)

//Detect MapAndreas Plugin [Slot: 1]
#if ((defined MapAndreas_FindZ_For2DCoord) && (!defined DISABLE_3D_TRYG_MAPANDREAS))
	#define Tryg3D_MapAndreas
	#define Tryg3D_MapAndreasVersion					(10201) //a.b.c 10000*a+100*b+c
	#define Tryg3D_Module_MapAndreas					(true)
	#if (!defined MapAndreas_GetAddress)
		#error [ADM] Update you MapAndreas.inc to v1.2.1
	#endif
#else
	#define Tryg3D_Module_MapAndreas					(false)
#endif

//Detect ColAndreas Plugin [Slot: 2]
#if ((defined COLANDREAS) && (!defined DISABLE_3D_TRYG_COLANDREAS))
	#define Tryg3D_ColAndreas
	#define Tryg3D_ColAndreasVersion					(10400) //a.b.c 10000*a+100*b+c
	#define Tryg3D_Module_ColAndreas					(true)
#else
	#define Tryg3D_Module_ColAndreas					(false)
#endif

#if !defined COLANDREAS_VERSION
	#define COLANDREAS_VERSION							(0)
#endif

//Detect YSF Plugin [Slot: 3]
#if ((defined _YSF_included) && (!defined DISABLE_3D_TRYG_YSF))
	#define Tryg3D_YSF
	#define Tryg3D_Module_YSF							(true)
	#if (!defined RemovePlayerForPlayer)
		#error [ADM] Update you YSF.inc to R18-2
	#endif
#else
	#define Tryg3D_Module_YSF							(false)
#endif

//Detect Streamer Plugin [Slot: 4]
#if ((defined Streamer_AppendArrayData) && (defined INVALID_STREAMER_ID) && (!defined DISABLE_3D_TRYG_STREAMER))
	#define Tryg3D_Streamer
	#define Tryg3D_StreamerVersion						(0x290)
	#define Tryg3D_Module_Streamer						(true)
	#if (!defined STREAMER_TYPE_ACTOR)
		#error [ADM] Update you streamer.inc to v2.9.0
	#endif
#else
	#define Tryg3D_Module_Streamer						(false)
#endif

//Detect FoxForeach Include [Slot: 5]
//Detect YSIForeach Include [Slot: 6]
#if ((defined _FoX_Foreach) && (!defined DISABLE_3D_TRYG_FOXFOREACH))
	#define Tryg3DForeach(%0) 							FoxForeach(%0,Character)
	#define Tryg3D_FoxForeach
	
	#define Tryg3D_Module_FoxForeach					(true)
	#define Tryg3D_Module_YSIForeach					(false)
#elseif ((defined _FOREACH_LOCAL_VERSION) && (!defined DISABLE_3D_TRYG_YSIFOREACH))
	#define Tryg3DForeach(%0)							foreach(new %0 : Character)
	#define Tryg3D_YSIForeach
	
	#define Tryg3D_Module_FoxForeach					(false)
	#define Tryg3D_Module_YSIForeach					(true)
#else
	#define Tryg3DForeach(%0)							for(new %0 = 0, p_%0 = GetPlayerPoolSize(); %0 <= p_%0; %0++) if(IsPlayerConnected(%0))
	
	#define Tryg3D_Module_FoxForeach					(false)
	#define Tryg3D_Module_YSIForeach					(false)
#endif

//Detect FCNPC Plugin [Slot: 7]
#if ((defined _FCNPC_included) && (defined FCNPC_INCLUDE_VERSION) && (!defined DISABLE_3D_TRYG_FCNPC))
	#define Tryg3D_FCNPC
	#define Tryg3D_FCNPC_Version							(170) //a.b.c 100*a+10*b+c
	#define Tryg3D_Module_FCNPC							(true)
	#if (!defined MOVE_TYPE_AUTO || !defined MOVE_SPEED_AUTO)
		#error [ADM] Update you FCNPC.inc to v1.7.0
	#endif
#else
	#define Tryg3D_Module_FCNPC							(false)
#endif

//Detect Stream3D Module [Slot: 8]
#if defined ENABLE_3D_TRYG_STREAM3D
	#define Tryg3D_Stream3D
	#define Tryg3D_Module_Stream3D						(true)
#else
	#define Tryg3D_Module_Stream3D						(false)
#endif

//Detect Line3D Module [Slot: 9]
#if defined ENABLE_3D_TRYG_LINE3D
	#define Tryg3D_Line3D
	#define Tryg3D_Module_Line3D						(true)
#else
	#define Tryg3D_Module_Line3D						(false)
#endif

//Detect a_actor Include [Slot: 10]
#if ((defined _actor_included) && (!defined DISABLE_3D_TRYG_ACTOR))
	#define Tryg3D_Actor
	#define Tryg3D_Module_Actor							(true)
#else
	#define Tryg3D_Module_Actor							(false)
#endif

//Detect ATM Module [Slot: 11]
#if !defined DISABLE_3D_TRYG_ATM
	#define Tryg3D_ATM
	#define Tryg3D_Module_ATM							(true)
#else
	#define Tryg3D_Module_ATM							(false)
#endif

//Detect Anims Module [Slot: 12]
#if defined ENABLE_3D_TRYG_ANIMS
	#define Tryg3D_Anims
	#define Tryg3D_Module_Anims							(true)
#else
	#define Tryg3D_Module_Anims							(false)
#endif

//Detect i_quat Include by IllidanS4 [Slot: 102]
#if ((defined GetVehicleRotation) && (defined VectorRelToAbsQuat))
	#define Tryg3D_i_quat
#endif

//Detect Prot [Slot: 999]
#define Tryg3D_Function::								stock
#define Tryg3D_Deprecated::								stock
#define Tryg3D_Public::%0(%1)							forward %0(%1); public %0(%1)
#define T3D:											v3D
#define Tryg3D::										Tryg3D_ 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Symbols                                                                                                                          *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#if !defined TRYG3D_ELEMENT_TAG
	#define TRYG3D_ELEMENT_TAG							{Text3D,DynamicObject,DynamicPickup,DynamicCP,DynamicRaceCP,DynamicMapIcon,DynamicText3D,DynamicArea,DynamicActor,_}:
#endif

#if !defined FLOAT_PI
	#define FLOAT_PI		 							(3.14159265358979323846)
#endif

#if !defined FLOAT_EULER
	#define FLOAT_EULER									(2.718281828459)
#endif

#if !defined FLOAT_NAN
	#define FLOAT_NAN 									(Float:0xFFFFFFFF)
#endif

#if !defined FLOAT_DEFECT
	#define FLOAT_DEFECT								(0.000001)
#endif

#if !defined INVALID_ROTATION
	#define INVALID_ROTATION							(-1000.0)
#endif

#if !defined VBTP
	#define VBTP 										(0x7FFFFFFF)
#endif

#if !defined VLTP
	#define VLTP 										(0x80000000)
#endif

#if !defined FLOAT_INFINITY
    #define FLOAT_INFINITY 								(Float:0x7F800000)
#endif

#if !defined MAX_POLYGON_POINTS
	#define MAX_POLYGON_POINTS 							(256)
#endif

#if !defined VEHICLE_SPEED_MULTIPLIER
	#define VEHICLE_SPEED_MULTIPLIER 					(170.0)
#endif

#if !defined PLAYER_SPEED_MULTIPLIER
	#define PLAYER_SPEED_MULTIPLIER						(1.0)
#endif

#if !defined INVALID_MOVE_TIME
	#define INVALID_MOVE_TIME 							(-1)
#endif

#if !defined INVALID_MOVE_SPEED
	#define INVALID_MOVE_SPEED							(-1.0)
#endif

#if !defined VERTICAL_CAMERA_RADIUS
	#define VERTICAL_CAMERA_RADIUS 						(55.0) // 27.5 * 2
#endif

#if !defined HORIZONTAL_CAMERA_RADIUS
	#define HORIZONTAL_CAMERA_RADIUS					(70.0) // 35.0 * 2
#endif

//Vehicle Flags
#define VF_STREET										(0b0000000000000001)
#define VF_AIRBORNE										(0b0000000000000010)
#define VF_NATATORIAL									(0b0000000000000100)
#define VF_MILITARY										(0b0000000000001000)
#define VF_TRAIN										(0b0000000000010000)
#define VF_RC		 									(0b0000000000100000)
#define VF_CARRIAGE 									(0b0000000001000000)
#define VF_AIRPLANE										(0b0000000010000000)
#define VF_HELICOPTER 									(0b0000000100000000)
#define VF_BIKES	 									(0b0000001000000000)
#define VF_TRAILER										(0b0000010000000000)
#define VF_TOWABLE										(0b0000100000000000)
#define VF_POLICE		 								(0b0001000000000000)

//Player Position Flag
#if defined Tryg3D_ColAndreas
	#define POSITION_FLAG_WORLD							(0b0000000000000001)
	#define POSITION_FLAG_INTERIOR						(0b0000000000000010)
	#define POSITION_FLAG_AIR							(0b0000000000000100)
	#define POSITION_FLAG_GROUND						(0b0000000000001000)
	#define POSITION_FLAG_WATER							(0b0000000000010000)
	#define POSITION_FLAG_UNDERWATER					(0b0000000000100000)
	#define POSITION_FLAG_UNDERGROUND					(0b0000000001000000)
#endif

#if (!defined VEHICLE_PART_RFTIRE)
	#define VEHICLE_PART_RFTIRE 						(1)	// Right Front tire
	#define VEHICLE_PART_LFTIRE 						(2)	// Left Front tire
	#define VEHICLE_PART_RRTIRE 						(3)	// Right Rear tire
	#define VEHICLE_PART_LRTIRE 						(4)	// Left Rear tire
	#define VEHICLE_PART_HOOD 							(5)	// In Front
	#define VEHICLE_PART_TRUNK 							(6)	// Behind
#endif

#define VEHICLE_PART_ROOF 								(7)	// Roof
#define VEHICLE_PART_CHASSIS							(8)	// Chassis
#define VEHICLE_PART_PETROLCAP							(9) // Petrolcap 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Enums/Variables                                                                                                                  *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

enum element_orientation {
	o_left,
	o_right,
	o_up,
	o_down,
	o_front,
	o_back
}

enum Item3D_Type {
	item_player,
	item_npc,
	item_actor,
	item_object,
	item_vehicle,
	item_dynamic_object,
	item_dynamic_pickup,
	item_dynamic_cp,
	item_dynamic_racecp,
	item_dynamic_mapicon,
	item_dynamic_3dtext,
	item_dynamic_actor
}

enum Vectors3D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z, Float:T3D:A
}

enum Orions3D {
	Float:T3D:orion, Float:T3D:lon, Float:T3D:lat
}

enum Float3D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z,
	Float:T3D:rX, Float:T3D:rY, Float:T3D:rZ,
	
	Float:T3D:tX, Float:T3D:tY, Float:T3D:tZ,
	
	T3D:VW, T3D:INT, Float:T3D:SPEED
}

enum Float4D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z,
	Float:T3D:rX, Float:T3D:rY, Float:T3D:rZ,
	
	Float:T3D:tX, Float:T3D:tY, Float:T3D:tZ,
	
	T3D:VW, T3D:INT, T3D:TL, Float:T3D:SPEED
}

enum LongFloat3D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z,
	Float:T3D:rX, Float:T3D:rY, Float:T3D:rZ,
	
	Float:T3D:tX, Float:T3D:tY, Float:T3D:tZ,
	Float:T3D:trX, Float:T3D:trY, Float:T3D:trZ,
	
	Float:T3D:VecX, Float:T3D:VecY, Float:T3D:VecZ,
	
	T3D:VW, T3D:INT, Float:T3D:SPEED
}

enum LongFloat4D {
	Float:T3D:X, Float:T3D:Y, Float:T3D:Z,
	Float:T3D:rX, Float:T3D:rY, Float:T3D:rZ,
	
	Float:T3D:tX, Float:T3D:tY, Float:T3D:tZ,
	Float:T3D:trX, Float:T3D:trY, Float:T3D:trZ,
	
	Float:T3D:VecX, Float:T3D:VecY, Float:T3D:VecZ,
	
	T3D:VW, T3D:INT, T3D:TL, Float:T3D:SPEED
}

enum OrientationCube3D {
	o_left_back_down,
	o_right_back_down,
	o_right_front_down,
	o_left_front_down,
	o_left_back_up,
	o_right_back_up,
	o_right_front_up,
	o_left_front_up
}

#if defined Tryg3D_Stream3D
	enum StreamType {
		s_invalid,
		s_circle,
		s_cylinder2d,
		s_cylinder3d,
		s_sphere,
		s_rectangle,
		s_cube2d,
		s_cube3d,
		s_circularsector,
		s_sphericalsector,
		s_cone,
		s_ellipse,
		s_ellipticalcyl2d
	}

	enum Stream3D {
		StreamType:T3D:type,
		
		Float:T3D:X,	Float:T3D:Y,	Float:T3D:Z,
		
		Float:T3D:minX,	Float:T3D:minY,	Float:T3D:minZ,
		Float:T3D:maxX,	Float:T3D:maxY,	Float:T3D:maxZ,
		
		Float:T3D:R
	}
#endif

#if defined Tryg3D_Line3D
	enum LinePoint3D {
		bool:T3D:PointUsed,
		Float:T3D:X,
		Float:T3D:Y,
		Float:T3D:Z,
		Float:T3D:rX,
		Float:T3D:rY,
		Float:T3D:rZ
	}
#endif

static const Float:Cube3DOffset[OrientationCube3D][3] = {
	{-1.0,-1.0,-1.0},	//left - back - down
	{1.0,-1.0,-1.0},	//right - back - down
	{1.0,1.0,-1.0},		//right - front - down
	{-1.0,1.0,-1.0},	//left - front - down
	{-1.0,-1.0,1.0},	//left - back - up
	{1.0,-1.0,1.0},		//right - back - up
	{1.0,1.0,1.0},		//right - front - up
	{-1.0,1.0,1.0}		//left - front - up
};

new Float:Tryg3D::StreamDistance = 300.0;

new const Float:Tryg3D::WeaponDamage[] = {
	1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,82.5,0.0,1.0,9.9,46.2,0.0,8.25,13.2,46.2,3.3,3.3,4.95,6.6,8.25,
	9.9,9.9,6.6,24.75,41.25,82.5,82.5,1.0,46.2,82.5,0.0,0.33,0.33,0.0,0.0,0.0,0.0,0.0,2.64,9.9,330.0,82.5,1.0,1.0,165.0
}; 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Fixes                                                                                                                            *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
 
#if !defined isnull
	#define isnull(%1) 									((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif

#if !defined CreateExplosionForPlayer
	native CreateExplosionForPlayer(playerid,Float:X,Float:Y,Float:Z,type,Float:Radius);
#endif
 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * MapAndreas Update                                                                                                                *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#if defined Tryg3D_ColAndreas
	
	//ColAndreas Version
	#define IsMapAndreasInit							Tryg3D::IsColAndreasInit
	#define SafeMapAndreasInit							Tryg3D::SafeColAndreasInit
	
	Tryg3D::Function:: Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0){
		if(x <= -3000.0 || x >= 3000.0 || y <= -3000.0 || y >= 3000.0){
			z = 0.0;
		} else {
			CA_FindZ_For2DCoord(x,y,z);
		}
		return z;
	}
	
#elseif defined Tryg3D_MapAndreas

	//MapAndreas Version
	#define IsMapAndreasInit							Tryg3D::IsMapAndreasInit
	#define SafeMapAndreasInit							Tryg3D::SafeMapAndreasInit
	
	Tryg3D::Function:: Float:MapAndreasFindZ(Float:x,Float:y,&Float:z=0.0){
		if(x <= -3000.0 || x >= 3000.0 || y <= -3000.0 || y >= 3000.0){
			z = 0.0;
		} else {
			MapAndreas_FindZ_For2DCoord(x,y,z);
		}
		return z;
	}
	
#endif

//Define FindZ Precision
#if defined Tryg3D_ColAndreas
	#define Tryg3D_MapAndreasFindZ						CA_FindZ_For2DCoord
	#define Tryg3DMapAndreasFindZ						Tryg3D::MapAndreasFindZ
#elseif defined Tryg3D_MapAndreas
	#define Tryg3D_MapAndreasFindZ						MapAndreasFindZ
	#define Tryg3DMapAndreasFindZ						Tryg3D::MapAndreasFindZ
#endif 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Complementary Functions                                                                                                          *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#define abs(%0)											(((%0) < 0)?(-(%0)):((%0)))
#define fabs(%0)										(((%0) < 0.0)?(-(%0)):((%0)))

#define	sqrtN(%0,%1)									floatpower((%0),(1.0/(%1)))

#define IsEven(%0)										((((%0) % 2) == 0)?(true):(false))
#define power(%0,%1)									(floatround(floatpower((%0),(%1)))) 
 
//Author: hesambia random.inc
Tryg3D::Function:: Float:RandomFloat(Float:min,Float:max,accuracy = 4){
	if(min >= max) return 0.0;
	if(min < 0.0 || max < 0.0) return 0.0;
	if(accuracy < 1 || accuracy > 6) accuracy = 4;
	new T3D:divValue = floatround(floatpower(10.0,accuracy));
	return random(floatround(max)-floatround(min))+min+(random(T3D:divValue)/T3D:divValue);
} 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Internal Functions                                                                                                               *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#define single_clock(%1,%2)								((360.0/(%1))*(%2))
#define even_clock(%1,%2)								((360.0/(%1))*(2*(%2)))
#define uneven_clock(%1,%2)								((360.0/(%1))*((2*(%2))-1))

#define NLTZ(%0)										(((%0) < 0)?(0):(%0))
#define NMTZ(%0)										(((%0) > 0)?(0):(%0))
#define NLTZF(%0)										(((%0) < 0.0)?(0.0):(%0))
#define NMTZF(%0)										(((%0) > 0.0)?(0.0):(%0))

#define NLTV(%0,%1)										(((%0) < (%1))?(%1):(%0))
#define NMTV(%0,%1)										(((%0) > (%1))?(%1):(%0))
#define NLTVF(%0,%1)									(((%0) < (%1))?(%1):(%0))
#define NMTVF(%0,%1)									(((%0) > (%1))?(%1):(%0))

//swapvars by Crayder
#define Tryg3D_SwapInt(%0,%1)							(((%0) ^= (%1)), ((%1) ^= (%0)), ((%0) ^= (%1)))

#define Tryg3D_GetWeaponDamage(%0)						Tryg3D::WeaponDamage[(%0)]
 
 
Tryg3D::Function:: CompRotation(rotation,&crotation=0){
	crotation = rotation;
	while(crotation < 0) crotation += 360;
	while(crotation >= 360) crotation -= 360;
	return crotation;
} 
 
Tryg3D::Function:: Float:CompRotationFloat(Float:rotation,&Float:crotation=0.0){
	crotation = rotation;
	while(crotation < 0.0) crotation += 360.0;
	while(crotation >= 360.0) crotation -= 360.0;
	return crotation;
} 
 
Tryg3D::Function:: DeCompRotation(rotation,&crotation=0){
	crotation = rotation;
	while(crotation >= 180) crotation -= 360;
	while(crotation < -180) crotation += 360;
	return crotation;
} 
 
Tryg3D::Function:: Float:DeCompRotationFloat(Float:rotation,&Float:crotation=0.0){
	crotation = rotation;
	while(crotation >= 180.0) crotation -= 360.0;
	while(crotation < -180.0) crotation += 360.0;
	return crotation;
} 
 
Tryg3D::Function:: bool:IsRotationTest(Float:rotation,Float:r_min,Float:r_max){
	rotation = CompRotationFloat(rotation);
	r_min = CompRotationFloat(r_min);
	r_max = CompRotationFloat(r_max);
	if(r_min > r_max){
		if(((-100.0*FLOAT_DEFECT) <= rotation <= r_max+(100*FLOAT_DEFECT)) || (r_min-(100*FLOAT_DEFECT) <= rotation <= 360.0+(100*FLOAT_DEFECT))) return true;
	} else {
		if(r_min-(100.0*FLOAT_DEFECT) <= rotation <= r_max+(100.0*FLOAT_DEFECT)) return true;
	}
	return false;
} 
 
Tryg3D::Function:: bool:Tryg3D::IsPlayerSpawned(playerid){
	#if defined ENABLE_3D_TRYG_TIMELINE_SYNC
		if(!GetPVarInt(playerid,"T3D:PlayerVisible")) return false;
	#endif
	new T3D:pstate = GetPlayerState(playerid);
	if(T3D:pstate != 1 && T3D:pstate != 2 && T3D:pstate != 3) return false;
	return true;
} 
 
Tryg3D::Function:: Tryg3D::GivePlayerDamage(targetid,Float:amount,playerid,weaponid,bodypart){
	new Float:T3D:health,Float:T3D:armour;
	GetPlayerArmour(targetid,T3D:armour);
	GetPlayerHealth(targetid,T3D:health);
	CallLocalFunction("OnPlayerGiveDamage","ddfdd",playerid,targetid,amount,weaponid,bodypart);
	CallLocalFunction("OnPlayerTakeDamage","ddfdd",targetid,playerid,amount,weaponid,bodypart);
	if(T3D:armour >= amount){
		SetPlayerArmour(targetid,T3D:armour-amount);
	} else if(T3D:armour < amount){
		amount -= T3D:armour;
		SetPlayerArmour(targetid,0.0);
		if(T3D:health-amount <= 0.0){
			CallRemoteFunction("OnPlayerDeath","ddd",targetid,playerid,weaponid);
			SpawnPlayer(targetid);
		} else {
			SetPlayerHealth(targetid,T3D:health-amount);
		}
	} else {
		if(T3D:health-amount <= 0.0){
			CallRemoteFunction("OnPlayerDeath","ddd",targetid,playerid,weaponid);
			SpawnPlayer(targetid);
		} else {
			SetPlayerHealth(targetid,T3D:health-amount);
		}
	}
} 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Ivan_Ino VehiclePartPosition Functions                                                                                           *
 * Code anti-collision: YES                                                                                                         *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

//Original by Ivan_Ino Updated by Abyss Morgan SRC:https://github.com/Ino42O/VehiclePartPosition/blob/master/VehiclePartPosition.inc
Tryg3D::Function:: GetVehiclePartPos(vehicleid,partid,&Float:tx,&Float:ty,&Float:tz,Float:offset_x=0.0,Float:offset_y=0.0,Float:offset_z=0.0){
	new Float:ox,Float:oy,Float:oz,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz;
	GetVehiclePos(vehicleid,x,y,z);
	Tryg3D::GetVehicleRotation(vehicleid,rx,ry,rz);
	switch(partid){
		case VEHICLE_PART_RFTIRE: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_WHEELSFRONT,ox,oy,oz);
		}
		case VEHICLE_PART_LFTIRE: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_WHEELSFRONT,ox,oy,oz);
			ox *= (-1);
			offset_x *= (-1);
		}
		case VEHICLE_PART_RRTIRE: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_WHEELSREAR,ox,oy,oz);
		}
		case VEHICLE_PART_LRTIRE: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_WHEELSREAR,ox,oy,oz);
			ox *= (-1);
			offset_x *= (-1);
		}
		case VEHICLE_PART_HOOD: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_SIZE,ox,oy,oz);
			oy /= 2.0;
			ox = oz = 0.0;
		}
		case VEHICLE_PART_TRUNK: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_SIZE,ox,oy,oz);
			oy /= (-2.0);
			offset_y *= (-1);
			ox = oz = 0.0;
		}
		case VEHICLE_PART_ROOF: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_SIZE,ox,oy,oz);
			oz /= 2.0;
			ox = oy = 0.0;
		}
		case VEHICLE_PART_CHASSIS: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_SIZE,ox,oy,oz);
			oz /= (-2.0);
			offset_z *= (-1);
			ox = oy = 0.0;
		}
		case VEHICLE_PART_PETROLCAP: {
			GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_PETROLCAP,ox,oy,oz);
		}
	}
	ox += offset_x;
	oy += offset_y;
	oz += offset_z;
	ShiftOffsetToPosition(x,y,z, rx,ry,rz, ox,oy,oz, tx,ty,tz);
}
 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Nero_3D Rotations Functions                                                                                                      *
 * Code anti-collision: YES                                                                                                         *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
 
enum T3D:eulermode {
	// Proper / Classic Euler angles
	T3D:euler_xzx,
	T3D:euler_xyx,
	T3D:euler_yxy,
	T3D:euler_yzy,
	T3D:euler_zyz,
	T3D:euler_zxz,
	// Tait-Bryan angles
	T3D:euler_xzy,
	T3D:euler_xyz,
	T3D:euler_yxz,
	T3D:euler_yzx,
	T3D:euler_zyx, // pitch roll yaw
	T3D:euler_zxy // sa-mp
}

const T3D:eulermode: T3D:euler_default = T3D:euler_zxy; 
 
//GetRotationMatrixFromEuler by Nero_3D
Tryg3D::Function:: Tryg3D::GetRotationMatrixEuler(Float:matrix[][],Float:rx,Float:ry,Float:rz,T3D:eulermode:mode=T3D:euler_default){
	// could be done with matrix multiplication but would be slower
	new Float:cosX = floatcos(rx,degrees),
		Float:cosY = floatcos(ry,degrees),
		Float:cosZ = floatcos(rz,degrees),
		Float:sinX = floatsin(rx,degrees),
		Float:sinY = floatsin(ry,degrees),
		Float:sinZ = floatsin(rz,degrees);

	switch(mode){
		//Proper Euler angles - 1(rx), 2(ry), 3(rz)
		case T3D:euler_xzx: {
			matrix[0][0] = cosY;
			matrix[0][1] = -cosZ * sinY;
			matrix[0][2] = sinY * sinZ;
			matrix[1][0] = cosX * sinY;
			matrix[1][1] = cosX * cosY * cosZ - sinX * sinZ;
			matrix[1][2] = -cosZ * sinX - cosX * cosY * sinZ;
			matrix[2][0] = sinX * sinY;
			matrix[2][1] = cosX * sinZ + cosY * cosZ * sinX;
			matrix[2][2] = cosX * cosZ - cosY * sinX * sinZ;
		}
		case T3D:euler_xyx: {
			matrix[0][0] = cosY;
			matrix[0][1] = sinY * sinZ;
			matrix[0][2] = cosZ * sinY;
			matrix[1][0] = sinX * sinY;
			matrix[1][1] = cosX * cosZ - cosY * sinX * sinZ;
			matrix[1][2] = -cosX * sinZ - cosY * cosZ * sinX;
			matrix[2][0] = -cosX * sinY;
			matrix[2][1] = cosZ * sinX + cosX * cosY * sinZ;
			matrix[2][2] = cosX * cosY * cosZ - sinX * sinZ;
		}
		case T3D:euler_yxy: {
			matrix[0][0] = cosX * cosZ - cosY * sinX * sinZ;
			matrix[0][1] = sinX * sinY;
			matrix[0][2] = cosX * sinZ + cosY * cosZ * sinX;
			matrix[1][0] = sinY * sinZ;
			matrix[1][1] = cosY;
			matrix[1][2] = -cosZ * sinY;
			matrix[2][0] = -cosZ * sinX - cosX * cosY * sinZ;
			matrix[2][1] = cosX * sinY;
			matrix[2][2] = cosX * cosY * cosZ - sinX * sinZ;
		}
		case T3D:euler_yzy: {
			matrix[0][0] = cosX * cosY * cosZ - sinX * sinZ;
			matrix[0][1] = -cosX * sinY;
			matrix[0][2] = cosZ * sinX + cosX * cosY * sinZ;
			matrix[1][0] = cosZ * sinY;
			matrix[1][1] = cosY;
			matrix[1][2] = sinY * sinZ;
			matrix[2][0] = -cosX * sinZ - cosY * cosZ * sinX;
			matrix[2][1] = sinX * sinY;
			matrix[2][2] = cosX * cosZ - cosY * sinX * sinZ;
		}
		case T3D:euler_zyz: {
			matrix[0][0] = cosX * cosY * cosZ - sinX * sinZ;
			matrix[0][1] = -cosZ * sinX - cosX * cosY * sinZ;
			matrix[0][2] = cosX * sinY;
			matrix[1][0] = cosX * sinZ + cosY * cosZ * sinX;
			matrix[1][1] = cosX * cosZ - cosY * sinX * sinZ;
			matrix[1][2] = sinX * sinY;
			matrix[2][0] = -cosZ * sinY;
			matrix[2][1] = sinY * sinZ;
			matrix[2][2] = cosY;
		}
		case T3D:euler_zxz: {
			matrix[0][0] = cosX * cosZ - cosY * sinX * sinZ;
			matrix[0][1] = -cosX * sinZ - cosY * cosZ * sinX;
			matrix[0][2] = sinX * sinY;
			matrix[1][0] = cosZ * sinX + cosX * cosY * sinZ;
			matrix[1][1] = cosX * cosY * cosZ - sinX * sinZ;
			matrix[1][2] = -cosX * sinY;
			matrix[2][0] = sinY * sinZ;
			matrix[2][1] = cosZ * sinY;
			matrix[2][2] = cosY;
		}
		//Tait-Bryan angles - X(rx), Y(ry), Z(rz)
		case T3D:euler_xzy: {
			matrix[0][0] = cosZ * cosY;
			matrix[0][1] = -sinZ;
			matrix[0][2] = cosZ * sinY;
			matrix[1][0] = sinX * sinY + cosX * cosY * sinZ;
			matrix[1][1] = cosX * cosZ;
			matrix[1][2] = cosX * sinZ * sinY - cosY * sinX;
			matrix[2][0] = cosY * sinX * sinZ - cosX * sinY;
			matrix[2][1] = cosZ * sinX;
			matrix[2][2] = cosX * cosY + sinX * sinZ * sinY;
		}
		case T3D:euler_xyz: {
			matrix[0][0] = cosY * cosZ;
			matrix[0][1] = -cosY * sinZ;
			matrix[0][2] = sinY;
			matrix[1][0] = cosX * sinZ + cosZ * sinX * sinY;
			matrix[1][1] = cosX * cosZ - sinX * sinY * sinZ;
			matrix[1][2] = -cosY * sinX;
			matrix[2][0] = sinX * sinZ - cosX * cosZ * sinY;
			matrix[2][1] = cosZ * sinX + cosX * sinY * sinZ;
			matrix[2][2] = cosX * cosY;
		}
		case T3D:euler_yxz: {
			matrix[0][0] = cosY * cosZ + sinY * sinX * sinZ;
			matrix[0][1] = cosZ * sinY * sinX - cosY * sinZ;
			matrix[0][2] = cosX * sinY;
			matrix[1][0] = cosX * sinZ;
			matrix[1][1] = cosX * cosZ;
			matrix[1][2] = -sinX;
			matrix[2][0] = cosY * sinX * sinZ - cosZ * sinY;
			matrix[2][1] = cosY * cosZ * sinX + sinY * sinZ;
			matrix[2][2] = cosY * cosX;
		}
		case T3D:euler_yzx: {
			matrix[0][0] = cosY * cosZ;
			matrix[0][1] = sinY * sinX - cosY * cosX * sinZ;
			matrix[0][2] = cosX * sinY + cosY * sinZ * sinX;
			matrix[1][0] = sinZ;
			matrix[1][1] = cosZ * cosX;
			matrix[1][2] = -cosZ * sinX;
			matrix[2][0] = -cosZ * sinY;
			matrix[2][1] = cosY * sinX + cosX * sinY * sinZ;
			matrix[2][2] = cosY * cosX - sinY * sinZ * sinX;
		}
		case T3D:euler_zyx: { // pitch roll yaw
			matrix[0][0] = cosZ * cosY;
			matrix[0][1] = cosZ * sinY * sinX - cosX * sinZ;
			matrix[0][2] = sinZ * sinX + cosZ * cosX * sinY;
			matrix[1][0] = cosY * sinZ;
			matrix[1][1] = cosZ * cosX + sinZ * sinY * sinX;
			matrix[1][2] = cosX * sinZ * sinY - cosZ * sinX;
			matrix[2][0] = -sinY;
			matrix[2][1] = cosY * sinX;
			matrix[2][2] = cosY * cosX;
		}
		case T3D:euler_zxy: { // sa-mp
			matrix[0][0] = cosZ * cosY - sinZ * sinX * sinY;
			matrix[0][1] = -sinZ * cosX;
			matrix[0][2] = cosZ * sinY + sinZ * sinX * cosY;
			matrix[1][0] = sinZ * cosY + cosZ * sinX * sinY;
			matrix[1][1] = cosZ * cosX;
			matrix[1][2] = sinZ * sinY - cosZ * sinX * cosY;
			matrix[2][0] = -cosX * sinY;
			matrix[2][1] = sinX;
			matrix[2][2] = cosX * cosY;
		}
	}
} 
 
//MatrixRotate by Nero_3D
Tryg3D::Function:: Tryg3D::MatrixRotate(Float:matrix[][],Float:oX,Float:oY,Float:oZ,&Float:x,&Float:y,&Float:z){
	x += oX * matrix[0][0] + oY * matrix[0][1] + oZ * matrix[0][2]; // M * v | v = [oX, oY, oZ]
	y += oX * matrix[1][0] + oY * matrix[1][1] + oZ * matrix[1][2];
	z += oX * matrix[2][0] + oY * matrix[2][1] + oZ * matrix[2][2];
} 
 
//GetQuatFromEuler by Nero_3D
Tryg3D::Function:: Tryg3D::GetQuatFromEuler(Float:rx,Float:ry,Float:rz,&Float:qw,&Float:qx,&Float:qy,&Float:qz,T3D:eulermode:mode=T3D:euler_default){
	rx /= 2.0; // could be done with multiplication but would be slower
	ry /= 2.0;
	rz /= 2.0;

	new	Float:cosX = floatcos(rx,degrees),
		Float:cosY = floatcos(ry,degrees),
		Float:cosZ = floatcos(rz,degrees),
		Float:sinX = floatsin(rx,degrees),
		Float:sinY = floatsin(ry,degrees),
		Float:sinZ = floatsin(rz,degrees);

	switch(mode) {
		case T3D:euler_xzx: {
			qw = sinX * cosY * sinZ - cosX * cosY * cosZ;
			qx = cosX * cosY * sinZ + sinX * cosY * cosZ;
			qy = cosX * sinY * sinZ - sinX * sinY * cosZ;
			qz = cosX * sinY * cosZ + sinX * sinY * sinZ;
		}
		case T3D:euler_xyx: {
			qw = sinX * cosY * sinZ - cosX * cosY * cosZ;
			qx = cosX * cosY * sinZ + sinX * cosY * cosZ;
			qy = cosX * sinY * cosZ + sinX * sinY * sinZ;
			qz = sinX * sinY * cosZ - cosX * sinY * sinZ;
		}
		case T3D:euler_yxy: {
			qw = sinX * cosY * sinZ - cosX * cosY * cosZ;
			qx = cosX * sinY * cosZ + sinX * sinY * sinZ;
			qy = cosX * cosY * sinZ + sinX * cosY * cosZ;
			qz = cosX * sinY * sinZ - sinX * sinY * cosZ;
		}
		case T3D:euler_yzy: {
			qw = sinX * cosY * sinZ - cosX * cosY * cosZ;
			qx = sinX * sinY * cosZ - cosX * sinY * sinZ;
			qy = cosX * cosY * sinZ + sinX * cosY * cosZ;
			qz = cosX * sinY * cosZ + sinX * sinY * sinZ;
		}
		case T3D:euler_zyz: {
			qw = sinX * cosY * sinZ - cosX * cosY * cosZ;
			qx = cosX * sinY * sinZ - sinX * sinY * cosZ;
			qy = cosX * sinY * cosZ + sinX * sinY * sinZ;
			qz = cosX * cosY * sinZ + sinX * cosY * cosZ;
		}
		case T3D:euler_zxz: {
			qw = sinX * cosY * sinZ - cosX * cosY * cosZ;
			qx = cosX * sinY * cosZ + sinX * sinY * sinZ;
			qy = sinX * sinY * cosZ - cosX * sinY * sinZ;
			qz = cosX * cosY * sinZ + sinX * cosY * cosZ;
		}
		case T3D:euler_xzy: {
			qw = cosX * cosY * cosZ + sinX * sinY * sinZ;
			qx = cosX * sinY * sinZ - sinX * cosY * cosZ;
			qy = sinX * cosY * sinZ - cosX * sinY * cosZ;
			qz = -(cosX * cosY * sinZ + sinX * sinY * cosZ);
		}
		case T3D:euler_xyz: {
			qw = sinX * sinY * sinZ - cosX * cosY * cosZ;
			qx = sinX * cosY * cosZ + cosX * sinY * sinZ;
			qy = cosX * sinY * cosZ - sinX * cosY * sinZ;
			qz = cosX * cosY * sinZ + sinX * sinY * cosZ;
		}
		case T3D:euler_yxz: {
			qw = cosX * cosY * cosZ + sinX * sinY * sinZ;
			qx = -(sinX * cosY * cosZ + cosX * sinY * sinZ);
			qy = sinX * cosY * sinZ - cosX * sinY * cosZ;
			qz = sinX * sinY * cosZ - cosX * cosY * sinZ;
		}
		case T3D:euler_yzx: {
			qw = sinX * sinY * sinZ - cosX * cosY * cosZ;
			qx = sinX * cosY * cosZ + cosX * sinY * sinZ;
			qy = cosX * sinY * cosZ + sinX * cosY * sinZ;
			qz = cosX * cosY * sinZ - sinX * sinY * cosZ;
		}
		case T3D:euler_zyx: {
			qw = cosX * cosY * cosZ + sinX * sinY * sinZ;
			qx = cosX * sinY * sinZ - sinX * cosY * cosZ;
			qy = -(cosX * sinY * cosZ + sinX * cosY * sinZ);
			qz = sinX * sinY * cosZ - cosX * cosY * sinZ;
		}
		case T3D:euler_zxy: {
			qw = sinX * sinY * sinZ - cosX * cosY * cosZ;
			qx = sinX * cosY * cosZ - cosX * sinY * sinZ;
			qy = cosX * sinY * cosZ + sinX * cosY * sinZ;
			qz = cosX * cosY * sinZ + sinX * sinY * cosZ;
		}
	}
} 
 
//QuatRotate by Nero_3D
Tryg3D::Function:: Tryg3D::QuatRotate(Float:qw,Float:qx,Float:qy,Float:qz,Float:oX,Float:oY,Float:oZ,&Float:tx,&Float:ty,&Float:tz){
	// wikipedia suggest this formula (a x b - cross prudct)
	// v + 2*r x (r x v + w*v) | q = w,r
	// 15 muls, 15 adds, 9 saves, 42 loads
	// but I used this one because it more compact (a.b - dot product)
	// 2*((r.v)*r + (0.5 - (|r.r|^2))*v + w * (r x v)) | q = w,r
	// 22 muls, 12 adds, 5 saves, 38 loads
	new Float:dot = qx * oX + qy * oY + qz * oZ,
		Float:abs = qw * qw - 0.5;

	tx += 2.0 * (dot * qx + abs * oX + qw * (qz * oY - qy * oZ));
	ty += 2.0 * (dot * qy + abs * oY + qw * (qx * oZ - qz * oX));
	tz += 2.0 * (dot * qz + abs * oZ + qw * (qy * oX - qx * oY));
} 
 
//EulerRotate by Nero_3D
Tryg3D::Function:: Tryg3D::EulerRotate(Float:rx,Float:ry,Float:rz,Float:oX,Float:oY,Float:oZ,&Float:tx,&Float:ty,&Float:tz,T3D:eulermode:mode=T3D:euler_default){
	Tryg3D::GetQuatFromEuler(rx,ry,rz,Float:mode,rx,ry,rz,mode);
	Tryg3D::QuatRotate(Float:mode,rx,ry,rz,oX,oY,oZ,tx,ty,tz);
} 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * General Functions                                                                                                                *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#define GetDistanceBetweenPoints1D(%1,%2)				VectorSize((%1)-(%2),0.0,0.0)
#define GetDistanceBetweenPoints2D(%1,%2,%3,%4)			VectorSize((%1)-(%3),(%2)-(%4),0.0)
#define GetDistanceBetweenPoints3D(%1,%2,%3,%4,%5,%6)	VectorSize((%1)-(%4),(%2)-(%5),(%3)-(%6))

#define CalculatePercent(%0,%1)							(((%0)/(%1))*100.0)

#define ShiftDegreeToRadian(%0)							((%0)*((FLOAT_PI*2)/360.0))
#define ShiftDegreeToRadianEx(%0)						((360.0-CompRotationFloat(%0))*(-((FLOAT_PI*2)/360.0)))
#define ShiftDegreeToGrades(%0)							((%0)*(10.0/9.0))
#define ShiftRadianToDegree(%0)							((%0)/((FLOAT_PI*2)/360.0))
#define ShiftRadianToDegreeEx(%0) 						(CompRotationFloat(floatabs(((%0)/((FLOAT_PI*2)/360.0))+360.0)))
#define ShiftRadianToGrades(%0)							(ShiftDegreeToGrades(ShiftRadianToDegree(%0)))
#define ShiftGradesToDegree(%0)							((%0)*0.9)
#define ShiftGradesToRadian(%0)							(ShiftDegreeToRadian(ShiftGradesToDegree(%0)))

#define ShiftRotationToVector(%0,%1,%2,%3,%4)			(GetPointInFront3D(0.0,0.0,0.0,(%0),(%1),1.0,(%2),(%3),(%4)))

#define RecoilFloat(%0,%1)								(((%0) >= 0.0)?((%0)+(%1)):((%0)-(%1)))

//old code version made by Zoutdaxv (modified version)
#define GetRotationFor2Point2D(%0,%1,%2,%3,%4)			(CompRotationFloat((atan2((%3)-(%1),(%2)-(%0))-90.0),(%4)))

#define IsPointInCylinder2D(%0,%1,%2,%3,%4,%5,%6,%7)	IsPointInCylinder3D((%0),(%1),(%2),(%3),(%4),(%5),(%3),(%4),(%6),(%7))
#define GetRandomPointOnCircle(%0,%1,%2,%3,%4)			GetPointInFront2D((%0),(%1),RandomFloat(0.0,360.0),(%2),(%3),(%4))
#define IsVehicleInRangeOfPoint(%0,%1,%2,%3,%4)			(GetVehicleDistanceFromPoint((%0),(%2),(%3),(%4)) <= (%1))

#define ShiftVectorToRotation(%0,%1,%2,%3,%4)			CompRotationFloat(-(acos(%2)-90.0),(%3)), CompRotationFloat((atan2((%1),(%0))-90.0),(%4))
#define IsPointInCircle(%0,%1,%2,%3,%4) 				(GetDistanceBetweenPoints2D((%0),(%1),(%2),(%3)) <= (%4))
#define IsPointInSphere(%0,%1,%2,%3,%4,%5,%6)			(GetDistanceBetweenPoints3D((%0),(%1),(%2),(%3),(%4),(%5)) <= (%6))
#define IsPointInRectangle(%1,%2,%3,%4,%5,%6)			(((%1) >= (%3) && (%1) <= (%5)) && ((%2) >= (%4) && (%2) <= (%6)))
#define IsPointInCube(%1,%2,%3,%4,%5,%6,%7,%8,%9)		(((%1) >= (%4) && (%1) <= (%7)) && ((%2) >= (%5) && (%2) <= (%8)) && ((%3) >= (%6) && (%3) <= (%9)))
#define GetPlayerCameraLookAt(%0,%1,%2,%3)				GetPointInFrontOfCamera3D((%0),(%1),(%2),(%3),5.0)
#define IsProbable(%0)									((random(100)+1) <= (%0))
#define GetVehicleFlags(%0)								GetVehicleFlagsByModel(GetVehicleModel(%0))
#define IsVehicleFlag(%0,%1)							((%0) & (%1))

//Universal boost
#define GetObjectDistanceFromPoint(%0,%1,%2,%3)			GetElementDistanceFromPoint((%0),item_object,(%1),(%2),(%3))
#define IsObjectInRangeOfPoint(%0,%1,%2,%3,%4)			(GetElementDistanceFromPoint((%0),item_object,(%2),(%3),(%4)) <= (%1))

#define GetPlayerObjectDistance(%1,%2)					GetElementsDistance((%1),item_player,(%1),item_object)
#define GetDistanceBetweenPlayers(%1,%2)				GetElementsDistance((%1),item_player,(%2),item_player)
#define GetDistanceBetweenVehicles(%1,%2)				GetElementsDistance((%1),item_vehicle,(%2),item_vehicle)
#define GetDistanceBetweenObjects(%1,%2)				GetElementsDistance((%1),item_object,(%2),item_object)
#define GetPlayerVehicleDistance(%1,%2)					GetElementsDistance((%1),item_player,(%2),item_object)

#define IsPlayerInCircle(%0,%1,%2,%3)					IsElementInCircle((%0),item_player,(%1),(%2),(%3))
#define IsPlayerInCylinder3D(%0,%1,%2,%3,%4,%5,%6,%7)	IsElementInCylinder3D((%0),item_player,(%1),(%2),(%3),(%4),(%5),(%6),(%7))
#define IsPlayerInCylinder2D(%0,%1,%2,%3,%4,%5)			IsElementInCylinder2D((%0),item_player,(%1),(%2),(%3),(%4),(%5))
#define IsPlayerInSphere(%0,%1,%2,%3,%4)				IsElementInSphere((%0),item_player,(%1),(%2),(%3),(%4))
#define IsPlayerInRectangle(%0,%1,%2,%3,%4)				IsElementInRectangle((%0),item_player,(%1),(%2),(%3),(%4))
#define IsPlayerInCube(%0,%1,%2,%3,%4,%5,%6)			IsElementInCube((%0),item_player,(%1),(%2),(%3),(%4),(%5),(%6))
#define IsPlayerInPolygon(%0,%1)						IsElementInPolygon((%0),item_player,(%1))
#define IsPlayerInCircularSector(%0,%1,%2,%3,%4,%5)		IsElementInCircularSector((%0),item_player,(%1),(%2),(%3),(%4),(%5))
#define IsPlayerInCone(%0,%1,%2,%3,%4,%5,%6,%7,%8)		IsElementInCone((%0),item_player,(%1),(%2),(%3),(%4),(%5),(%6),(%7),(%8))
#define IsPlayerInCube3D(%0,%1,%2,%3,%4,%5,%6,%7,%8,%9)	IsElementInCube3D((%0),item_player,(%1),(%2),(%3),(%4),(%5),(%6),(%7),(%8),(%9))
#define IsPlayerInEllipse(%0,%1,%2,%3,%4)				IsElementInEllipse((%0),item_player,(%1),(%2),(%3),(%4))
#define IsPlayerInEllipticalCylinder2D(%0,%1,%2,%3,%4,%5,%6)	IsElementInEllipticalCylinder2D((%0),item_player,(%1),(%2),(%3),(%4),(%5),(%6))
#define IsPlayerInSphericalSector(%0,%1,%2,%3,%4,%5,%6,%7,%8)	IsElementInSphericalSector((%0),item_player,(%1),(%2),(%3),(%4),(%5),(%6),(%7),(%8))

#define GetArcPointsFloor3D(%0,%1,%2,%3,%4,%5,%6,%7)		GetArcPoints3D((%0),(%1),(%2),(%3),(%4),(%5),0.0,(%6),(%7))
#define GetArcPointsCellar3D(%0,%1,%2,%3,%4,%5,%6,%7)		GetArcPoints3D((%0),(%1),(%2),(%3),(%4),(%5),180.0,(%6),(%7))
#define GetArcPointsStarboard3D(%0,%1,%2,%3,%4,%5,%6,%7)	GetArcPoints3D((%0),(%1),(%2),(%3),(%4),(%5),90.0,(%6),(%7))
#define GetArcPointsLarboard3D(%0,%1,%2,%3,%4,%5,%6,%7)		GetArcPoints3D((%0),(%1),(%2),(%3),(%4),(%5),270.0,(%6),(%7))

#define GetArcPointsFloor2D(%0,%1,%2,%3,%4,%5,%6) 			GetArcPointsFloor3D((%0),(%1),(%2),(%3),(%4),(%2),(%5),(%6))
#define GetArcPointsCellar2D(%0,%1,%2,%3,%4,%5,%6)			GetArcPointsCellar3D((%0),(%1),(%2),(%3),(%4),(%2),(%5),(%6))
#define GetArcPointsLarboard2D(%0,%1,%2,%3,%4,%5,%6)		GetArcPointsLarboard3D((%0),(%1),(%2),(%3),(%4),(%2),(%5),(%6))
#define GetArcPointsStarboard2D(%0,%1,%2,%3,%4,%5,%6)		GetArcPointsStarboard3D((%0),(%1),(%2),(%3),(%4),(%2),(%5),(%6))
 
 
Tryg3D::Function:: Tryg3D::EulerToQuat(Float:rx,Float:ry,Float:rz,&Float:qw,&Float:qx,&Float:qy,&Float:qz){
	rx /= 2.0;
	ry /= 2.0;
	rz /= 2.0;

	new	Float:cosX = floatcos(rx,degrees),
		Float:cosY = floatcos(ry,degrees),
		Float:cosZ = floatcos(rz,degrees),
		Float:sinX = floatsin(rx,degrees),
		Float:sinY = floatsin(ry,degrees),
		Float:sinZ = floatsin(rz,degrees);

	qw = sinX * sinY * sinZ - cosX * cosY * cosZ;
	qx = sinX * cosY * cosZ - cosX * sinY * sinZ;
	qy = cosX * sinY * cosZ + sinX * cosY * sinZ;
	qz = cosX * cosY * sinZ + sinX * sinY * cosZ;
} 
 
Tryg3D::Function:: Tryg3D::QuatToEuler(&Float:rx,&Float:ry,&Float:rz,Float:qw,Float:qx,Float:qy,Float:qz){
	CompRotationFloat(asin(2*qy*qz-2*qx*qw),rx);
	CompRotationFloat(-atan2(qx*qz+qy*qw,0.5-qx*qx-qy*qy),ry);
	CompRotationFloat(-atan2(qx*qy+qz*qw,0.5-qx*qx-qz*qz),rz);
} 
 
#if !defined Tryg3D_i_quat
	//GetVehicleRotation Created by IllidanS4
	Tryg3D::Function:: GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz){
		new Float:qw,Float:qx,Float:qy,Float:qz;
		GetVehicleRotationQuat(vehicleid,qw,qx,qy,qz);
		Tryg3D::QuatToEuler(rx,ry,rz,qw,qx,qy,qz);
	}
	
	#define Tryg3D_GetVehicleRotation			GetVehicleRotation
#else	
	Tryg3D::Function:: Tryg3D::GetVehicleRotation(vehicleid,&Float:rx,&Float:ry,&Float:rz){
		new Float:qw,Float:qx,Float:qy,Float:qz;
		GetVehicleRotationQuat(vehicleid,qw,qx,qy,qz);
		Tryg3D::QuatToEuler(rx,ry,rz,qw,qx,qy,qz);
	}
#endif 
 
Tryg3D::Function:: Float:GetEllipseRadius(Float:x,Float:y,Float:angle){
	if(x <= 0.0) return -1.0;
	new Float:theta = atan((y/x)*floattan(CompRotationFloat(angle),degrees));
	return floatsqroot((floatpower(x,2.0)*floatpower(floatsin(theta,degrees),2.0))+(floatpower(y,2.0)*floatpower(floatcos(theta,degrees),2.0)));
} 
 
Tryg3D::Function:: Float:GetLineSize2D(Float:points[][],maxpoints=sizeof(points)){
	if(maxpoints < 2) return 0.0;
	new Float:T3D:distance = 0.0;
	for(new i = 1; i < maxpoints; i++){
		T3D:distance += GetDistanceBetweenPoints2D(points[i-1][0],points[i-1][1],points[i][0],points[i][1]);
	}
	return T3D:distance;
} 
 
Tryg3D::Function:: Float:GetLineSize3D(Float:points[][],maxpoints=sizeof(points)){
	if(maxpoints < 2) return 0.0;
	new Float:T3D:distance = 0.0;
	for(new i = 1; i < maxpoints; i++){
		T3D:distance += GetDistanceBetweenPoints3D(points[i-1][0],points[i-1][1],points[i-1][2],points[i][0],points[i][1],points[i][2]);
	}
	return T3D:distance;
} 
 
Tryg3D::Function:: RecoilVector(&Float:vx,&Float:vy,&Float:vz,Float:sx,Float:sy,Float:sz){
	vx = RecoilFloat(vx,sx), vy = RecoilFloat(vy,sy), vz = RecoilFloat(vz,sz);
} 
 
Tryg3D::Function:: SetPlayerLookAtPlayer(playerid,targetid,cut = CAMERA_CUT){
	new Float:x,Float:y,Float:z;
	GetPlayerPos(targetid,x,y,z);
	SetPlayerCameraLookAt(playerid,x,y,z,cut);
}
 
 
Tryg3D::Function:: Float:GetVehicleSpeed(vehicleid){
	new Float:x,Float:y,Float:z;
	GetVehicleVelocity(vehicleid,x,y,z);
	return floatmul(VectorSize(x,y,z),VEHICLE_SPEED_MULTIPLIER);
} 
 
Tryg3D::Function:: Float:GetPlayerSpeed(playerid){
	new Float:x,Float:y,Float:z;
	GetPlayerVelocity(playerid,x,y,z);
	return floatmul(VectorSize(x,y,z),PLAYER_SPEED_MULTIPLIER);
} 
 
Tryg3D::Function:: GetVehicleFlagsByModel(modelid){
	new flag_value = 0;
	switch(modelid){
		case 425,548,417,487,497,563,469,447,488: flag_value += VF_AIRBORNE + VF_HELICOPTER;
		case 460,476,511,512,520,593,592,553,519,513,577: flag_value += VF_AIRBORNE + VF_AIRPLANE;
		case 539: flag_value += VF_AIRBORNE;
	}
	switch(modelid){
		case 425,520,432: flag_value += VF_MILITARY;
	}
	switch(modelid){
		case 472,473,493,595,484,430,453,452,446,454,539,447,460: flag_value += VF_NATATORIAL;
	}
	switch(modelid){
		case 441,464,465,501,564,594: flag_value += VF_RC;
	}
	switch(modelid){
		case 471,468,586,463,523,521,461,522,581,448,462,510,481,509: flag_value += VF_BIKES;
	}
	switch(modelid){
		case 435,450,584,590,591,606,607,608,610,611: flag_value += VF_TRAILER;
	}
	switch(modelid){
		case 449,537,538: flag_value += VF_TRAIN;
	}
	switch(modelid){
		case 569,570,590: flag_value += VF_CARRIAGE;
	}
	if(modelid == 539 || ((flag_value & VF_NATATORIAL != VF_NATATORIAL) && (flag_value & VF_AIRBORNE != VF_AIRBORNE))) flag_value += VF_STREET;
	switch(modelid){
		case 437,544,431,407,408,570,569,538,537,449,532,524,403,514,515,443,435,433,432,406: {	}

		default: {
			if(flag_value&VF_NATATORIAL!=VF_NATATORIAL && flag_value&VF_AIRBORNE!=VF_AIRBORNE && flag_value&VF_RC!=VF_RC && flag_value&VF_BIKES!=VF_BIKES){
				flag_value += VF_TOWABLE;
			}
		}

	}
	switch(modelid){
		case 416,523,427,490,407,544,596,598,597,599: flag_value += VF_POLICE;
	}
	return flag_value;
} 
 
Tryg3D::Function:: CountPlayers(bool:isplayer=true,bool:isnpc=true){
	new T3D:count = 0;
	Tryg3DForeach(i){
		if(IsPlayerNPC(i)){
			if(isnpc) T3D:count++;
		} else {
			if(isplayer) T3D:count++;
		}
	}
	return T3D:count;
} 
 
Tryg3D::Function:: CountVisiblePlayers(playerid,bool:isplayer=true,bool:isnpc=true){
	new T3D:count = 0;
	Tryg3DForeach(i){
		if(i != playerid && IsPlayerStreamedIn(i,playerid)){
			if(IsPlayerNPC(i)){
				if(isnpc) T3D:count++;
			} else {
				if(isplayer) T3D:count++;
			}
		}
	}
	return T3D:count;
} 
 
Tryg3D::Function:: CountVisibleVehicles(playerid){
	new T3D:count = 0;
	for(new i = 0, j = GetVehiclePoolSize(); i <= j; i++){
		if(IsValidVehicle(i) && IsVehicleStreamedIn(i,playerid)){
			T3D:count++;
		}
	}
	return T3D:count;
} 
 
Tryg3D::Function:: GetRandomHit(Float:x,Float:y,Float:z,range,&Float:tx,&Float:ty,&Float:tz){
	tx = x + (random(range * 2 + 1) - range);
	ty = y + (random(range * 2 + 1) - range);
	tz = z + (random(range * 2 + 1) - range);
} 
 
//Old code version, Updated by Nero_3D
Tryg3D::Function:: GetPointInFront2D(Float:x,Float:y,Float:rz,Float:radius,&Float:tx,&Float:ty){
	tx = x - (radius * floatsin(rz,degrees));
	ty = y + (radius * floatcos(rz,degrees));
} 
 
Tryg3D::Function:: bool:GetRotationFor2Point3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:rx,&Float:rz){
	new Float:radius = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
	if(radius <= 0.0) return false;
	CompRotationFloat(-(acos((tz-z)/radius)-90.0),rx);
	CompRotationFloat((atan2(ty-y,tx-x)-90.0),rz);
	return true;
} 
 
//new code version support 3D made by Abyss Morgan, Update by Nero_3D
Tryg3D::Function:: GetPointInFront3D(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	tx = x - (radius * floatcos(rx,degrees) * floatsin(rz,degrees));
	ty = y + (radius * floatcos(rx,degrees) * floatcos(rz,degrees));
	tz = z + (radius * floatsin(rx,degrees));
} 
 
Tryg3D::Function:: GetPointInFront3DEx(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	new Float:vx,Float:vy,Float:vz,Float:trx,Float:trz;
	Tryg3D::EulerRotate(rx,ry,rz,0.0,1.0,0.0,vx,vy,vz,T3D:euler_zyx);
	GetRotationFor2Point3D(0.0,0.0,0.0,vx,vy,vz,trx,trz);
	GetPointInFront3D(x,y,z,trx,trz,radius,tx,ty,tz); 
} 
 
Tryg3D::Function:: Float:GetPointInFrontOfPlayer(playerid,&Float:tx,&Float:ty,Float:radius){
	new Float:rz;
	GetPlayerPos(playerid,tx,ty,rz);
	if(IsPlayerInAnyVehicle(playerid)){
		GetVehicleZAngle(GetPlayerVehicleID(playerid),rz);
	} else {
		GetPlayerFacingAngle(playerid,rz);
	}
	GetPointInFront2D(tx,ty,rz,radius,tx,ty);
	return rz;
} 
 
Tryg3D::Function:: GetPlayerCameraRotation(playerid,&Float:rx,&Float:rz){
	new Float:mx,Float:my,Float:mz;
	GetPlayerCameraFrontVector(playerid,mx,my,mz);
	CompRotationFloat(-(acos(mz)-90.0),rx);
	CompRotationFloat((atan2(my,mx)-90.0),rz);
} 
 
Tryg3D::Function:: SetPlayerCameraRotation(playerid,Float:rx,Float:rz){
	new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz;
	GetPlayerCameraPos(playerid,x,y,z);
	GetPointInFront3D(x,y,z,rx,rz,1.0,tx,ty,tz);
	SetPlayerCameraLookAt(playerid,tx,ty,tz);
} 
 
Tryg3D::Function:: Float:GetPlayerCameraZAngle(playerid,&Float:rz=0.0){
	new Float:mx,Float:my,Float:mz;
	GetPlayerCameraFrontVector(playerid,mx,my,mz);
	CompRotationFloat((atan2(my,mx)-90.0),rz);
	return rz;
} 
 
Tryg3D::Function:: SetPlayerCameraZAngle(playerid,Float:rz){
	new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:rx,Float:tmp_float;
	GetPlayerCameraPos(playerid,x,y,z);
	GetPlayerCameraRotation(playerid,rx,tmp_float);
	GetPointInFront3D(x,y,z,rx,rz,1.0,tx,ty,tz);
	SetPlayerCameraLookAt(playerid,tx,ty,tz);
} 
 
Tryg3D::Function:: Float:GetPointInFrontOfCamera2D(playerid,&Float:tx,&Float:ty,Float:radius){
	new Float:x,Float:y,Float:rz;
	GetPlayerCameraPos(playerid,x,y,rz);
	GetPlayerCameraZAngle(playerid,rz);
	GetPointInFront2D(x,y,rz,radius,tx,ty);
	return rz;
} 
 
Tryg3D::Function:: ConvertMTARaceRotation(Float:rotation1,Float:rotation2,Float:rotation3,&Float:rx,&Float:ry,&Float:rz){
	rx = ShiftRadianToDegreeEx(rotation3);
	ry = ShiftRadianToDegreeEx(rotation2);
	rz = ShiftRadianToDegreeEx(rotation1);
} 
 
Tryg3D::Function:: ConvertToMTARaceRotation(Float:rx,Float:ry,Float:rz,&Float:rotation1,&Float:rotation2,&Float:rotation3){
	rotation3 = ShiftDegreeToRadianEx(rx);
	rotation2 = ShiftDegreeToRadianEx(ry);
	rotation1 = ShiftDegreeToRadianEx(rz);
} 
 
Tryg3D::Function:: GetMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:speed,&rtime=0){
	if(speed <= 0.0){
		rtime = INVALID_MOVE_TIME;
	} else {
		rtime = floatround((GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz)/speed)*1000.0);
	}
	return rtime;
} 
 
Tryg3D::Function:: GetSpeedForMoveTime(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:speed,rtime){
	if(rtime/1000.0 <= 0.0){
		speed = INVALID_MOVE_SPEED;
	} else {
		speed = (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz)/(rtime/1000.0));
	}
} 
 
Tryg3D::Function:: ShiftVectorRotation(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,&Float:tx,&Float:ty,&Float:tz){
	//Normalizing, but isn`t needed for the matrix rotation
	new Float:dist = VectorSize(x,y,z);
	if(dist <= 0.0){
		tx = x, ty = y, tz = z;
		return 0;
	}
	x /= dist, y /= dist, z /= dist;
	
	//Get rotation matrix from degrees
	new Float:T3D:matrix[3][3];
	Tryg3D::GetRotationMatrixEuler(T3D:matrix,rx,ry,rz);
	Tryg3D::MatrixRotate(T3D:matrix,x,y,z,tx,ty,tz);
	return 1;
}

 
 
Tryg3D::Function:: ShiftOffsetToPosition(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:offset_x,Float:offset_y,Float:offset_z,&Float:tx,&Float:ty,&Float:tz){
	new Float:px,Float:py,Float:pz;
	if(!ShiftVectorRotation(offset_x,offset_y,offset_z,rx,ry,rz,px,py,pz)){
		tx = x, ty = y, tz = z;
	} else {
		GetRotationFor2Point3D(0.0,0.0,0.0,px,py,pz,rx,rz);
		GetPointInFront3D(x,y,z,rx,rz,VectorSize(offset_x,offset_y,offset_z),tx,ty,tz);
	}
} 
 
Tryg3D::Function:: ShiftPositionToOffset(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,&Float:offset_x,&Float:offset_y,&Float:offset_z,Float:tx,Float:ty,Float:tz){
	new Float:px,Float:py,Float:pz,Float:trx,Float:trz,Float:dist = GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
	if(!GetRotationFor2Point3D(x,y,z,tx,ty,tz,trx,trz)){
		offset_x = x, offset_y = y, offset_z = z;
	} else {
		new Float:ex,Float:ey,Float:ez;
		GetPointInFront3D(0.0,0.0,0.0,trx,trz,1.0,px,py,pz);
		ShiftVectorRotation(px,py,pz,CompRotationFloat(-rx),CompRotationFloat(-ry),CompRotationFloat(-rz),ex,ey,ez);
		GetPointFor2Point3DEx(0.0,0.0,0.0,ex,ey,ez,dist,offset_x,offset_y,offset_z);
	}
} 
 
//QuatUpVector by Nero_3D
Tryg3D::Function:: GetQuatUpVector(Float:qw,Float:qx,Float:qy,Float:qz,&Float:vx,&Float:vy,&Float:vz){
	vx = 2.0*(qy*qw+qz*qx);
	vy = 2.0*(qz*qy-qx*qw);
	vz = 1.0-(2.0*(qx*qx+qy*qy));
} 
 
Tryg3D::Function:: bool:GetArcPoints3D(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:ry,Float:height,Float:points[][],max_points = sizeof(points)){
	if(max_points < 3) return false;
	if(height <= 0.0) return false;
	
	new Float:rx,Float:rz;
	if(!GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz)) return false;
	CompRotationFloat(ry,ry);
	
	new Float:px, Float:py, Float:pz,
		Float:cx, Float:cy, Float:cz,
		Float:center_dist = (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz)/2.0),
		Float:mercury = (180.0/max_points),
		Float:omega,
		idx = 0;
	
	GetPointInFront3D(x,y,z,rx,rz,center_dist,cx,cy,cz);
	for(new i = max_points-1; i >= 0; i--){
		CompRotationFloat(180.0-(mercury*idx),omega);
		GetPointInFront3D(0.0,0.0,0.0,omega,0.0,GetEllipseRadius(height,center_dist,omega),px,py,pz);
		ShiftOffsetToPosition(cx,cy,cz,rx,ry,rz,px,py,pz,points[idx][0],points[idx][1],points[idx][2]);
		idx++;
	}
	return true;
} 
 
Tryg3D::Function:: bool:GetPointToPointVector(Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,&Float:vx,&Float:vy,&Float:vz){
	new Float:rx,Float:rz;
	if(GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz)){
		ShiftRotationToVector(rx,rz,vx,vy,vz);
		return true;
	} else {
		vx = vy = vz = 0.0;
		return false;
	}
} 
 
Tryg3D::Function:: Float:GetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0){
	new Float:mx,Float:my;
	GetPlayerPos(playerid,mx,my,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	return rz;
} 
 
Tryg3D::Function:: Float:SetPlayerTargetAngle(playerid,Float:x,Float:y,&Float:rz=0.0){
	new Float:mx,Float:my;
	GetPlayerPos(playerid,mx,my,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	SetPlayerFacingAngle(playerid,rz);
	return rz;
} 
 
Tryg3D::Function:: Float:GetPlayerTargetPlayerAngle(playerid,targetid,&Float:rz=0.0){
	new Float:mx,Float:my,Float:x,Float:y;
	GetPlayerPos(playerid,mx,my,rz);
	GetPlayerPos(targetid,x,y,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	return rz;
} 
 
Tryg3D::Function:: Float:SetPlayerTargetPlayerAngle(playerid,targetid,&Float:rz=0.0){
	new Float:mx,Float:my,Float:x,Float:y;
	GetPlayerPos(playerid,mx,my,rz);
	GetPlayerPos(targetid,x,y,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	SetPlayerFacingAngle(playerid,rz);
	return rz;
} 
 
Tryg3D::Function:: CreateDynamicExplosion(Float:x,Float:y,Float:z,type,Float:radius,worldid = -1,interiorid = -1,playerid = -1,Float:distance = 200.0){
	if(playerid == -1){
		Tryg3DForeach(i){
			new Float:px, Float:py, Float:pz;
			if(IsPlayerInAnyVehicle(i)){
				GetVehiclePos(GetPlayerVehicleID(i),px,py,pz);
			} else {
				GetPlayerPos(i,px,py,pz);
			}
			if((GetPlayerInterior(i) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(i) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
				CreateExplosionForPlayer(i,x,y,z,type,radius);
			}
		}
	} else {
		if(IsPlayerConnected(playerid)){
			new Float:px, Float:py, Float:pz;
			if(IsPlayerInAnyVehicle(playerid)){
				GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			} else {
				GetPlayerPos(playerid,px,py,pz);
			}
			if((GetPlayerInterior(playerid) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(playerid) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
				CreateExplosionForPlayer(playerid,x,y,z,type,radius);
			}
		}
	}
} 
 
Tryg3D::Function:: GetWeaponShotPos(playerid,hittype,&Float:fx,&Float:fy,&Float:fz){
	new Float:ox,Float:oy,Float:oz;
	switch(hittype){
		case BULLET_HIT_TYPE_VEHICLE, BULLET_HIT_TYPE_OBJECT, BULLET_HIT_TYPE_PLAYER_OBJECT, BULLET_HIT_TYPE_PLAYER: {
			GetPlayerLastShotVectors(playerid,ox,oy,oz,fx,fy,fz);
		}
	}
} 
 
//Original code by Crayder
Tryg3D::Function:: ShiftLineRotation(Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:rx,Float:ry,Float:rz,&Float:nX,&Float:nY,&Float:nZ){
	//Get difference
	eX -= sX, eY -= sY, eZ -= sZ;
	//Get rotation matrix from degrees
	new Float:T3D:matrix[3][3];
	Tryg3D::GetRotationMatrixEuler(T3D:matrix,rx,ry,rz);
	Tryg3D::MatrixRotate(T3D:matrix,eX,eY,eZ,nX,nY,nZ);
}
 
 
//Original code by Crayder
Tryg3D::Function:: ShiftLineRotationVector(Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,Float:rx,Float:ry,Float:rz,&Float:nX,&Float:nY,&Float:nZ){
	//Get difference
	eX -= sX, eY -= sY, eZ -= sZ;
	
	//Normalizing, but isn`t needed for the matrix rotation
	new Float:dist = VectorSize(eX,eY,eZ);
	if(dist <= 0.0){
		nX = eX, nY = eY, nZ = eZ;
		return 0;
	}
	eX /= dist, eY /= dist, eZ /= dist;
	
	//Get rotation matrix from degrees
	new Float:T3D:matrix[3][3];
	Tryg3D::GetRotationMatrixEuler(T3D:matrix,rx,ry,rz);
	Tryg3D::MatrixRotate(T3D:matrix,eX,eY,eZ,nX,nY,nZ);
	return 1;
}
 
 
Tryg3D::Function:: GetCube3DPoint(OrientationCube3D:orientation,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z,&Float:tx,&Float:ty,&Float:tz){
	ShiftOffsetToPosition(x,y,z,rx,ry,rz,(Cube3DOffset[orientation][0]*size_x),(Cube3DOffset[orientation][1]*size_y),(Cube3DOffset[orientation][2]*size_z),tx,ty,tz);
} 
 
Tryg3D::Function:: Float:GetPointInFrontOfVehicle2D(vehicleid,&Float:tx,&Float:ty,Float:radius){
	new Float:rx,Float:ry,Float:rz,Float:x,Float:y;
	GetVehiclePos(vehicleid,x,y,rz);
	Tryg3D::GetVehicleRotation(vehicleid,rx,ry,rz);
	GetPointInFront2D(x,y,rz,radius,tx,ty);
	return rz;
} 
 
Tryg3D::Function:: GetPointInFrontOfVehicle3D(vehicleid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
	new Float:ry,Float:x,Float:y,Float:z;
	GetVehiclePos(vehicleid,x,y,z);
	Tryg3D::GetVehicleRotation(vehicleid,rx,ry,rz);
	GetPointInFront3D(x,y,z,rx,rz,radius,tx,ty,tz);
} 
 
Tryg3D::Function:: GetPointInFrontOfCamera3D(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
	new Float:x,Float:y,Float:z;
	GetPlayerCameraPos(playerid,x,y,z);
	GetPlayerCameraRotation(playerid,rx,rz);
	GetPointInFront3D(x,y,z,rx,rz,radius,tx,ty,tz);
} 
 
Tryg3D::Function:: bool:IsPlayerLookAtSky(playerid){
	new Float:rx,Float:rz;
	GetPlayerCameraRotation(playerid,rx,rz);
	return (rx > 0.0 && rx <= 90.0);
} 
 
Tryg3D::Function:: GetPointFor2Point2D(Float:x1,Float:y1,Float:x2,Float:y2,Float:percent_size,&Float:tx,&Float:ty){
	new Float:rz;
	GetRotationFor2Point2D(x1,y1,x2,y2,rz);
	GetPointInFront2D(x1,y1,rz,(GetDistanceBetweenPoints2D(x1,y1,x2,y2)*(percent_size/100.0)),tx,ty);
} 
 
Tryg3D::Function:: GetPointFor2Point3D(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:percent_size,&Float:tx,&Float:ty,&Float:tz){
	new Float:rx,Float:rz;
	GetRotationFor2Point3D(x1,y1,z1,x2,y2,z2,rx,rz);
	GetPointInFront3D(x1,y1,z1,rx,rz,(GetDistanceBetweenPoints3D(x1,y1,z1,x2,y2,z2)*(percent_size/100.0)),tx,ty,tz);
}
 
 
Tryg3D::Function:: GetPointFor2Point2DEx(Float:x1,Float:y1,Float:x2,Float:y2,Float:distance,&Float:tx,&Float:ty){
	new Float:rz;
	GetRotationFor2Point2D(x1,y1,x2,y2,rz);
	GetPointInFront2D(x1,y1,rz,distance,tx,ty);
} 
 
Tryg3D::Function:: GetPointFor2Point3DEx(Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2,Float:distance,&Float:tx,&Float:ty,&Float:tz){
	new Float:rx,Float:rz;
	GetRotationFor2Point3D(x1,y1,z1,x2,y2,z2,rx,rz);
	GetPointInFront3D(x1,y1,z1,rx,rz,distance,tx,ty,tz);
}
 
 
//DistanceFromPointToLine by Crayder
Tryg3D::Function:: Float:GetDistanceFromPointToLine(Float:px,Float:py,Float:pz,Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,&Float:iX=0.0,&Float:iY=0.0,&Float:iZ=0.0){
	new Float:dist = GetDistanceBetweenPoints3D(eX,eY,eZ,sX,sY,sZ);
	if(dist <= 0.0) return -1.0;
	new Float:T3D:U = (((px - sX) * (eX - sX)) + ((py - sY) * (eY - sY)) + ((pz - sZ) * (eZ - sZ))) / (dist*dist);
	if(T3D:U < 0.0 || T3D:U > 1.0) return -1.0;

	iX = sX + T3D:U * (eX - sX);
	iY = sY + T3D:U * (eY - sY);
	iZ = sZ + T3D:U * (eZ - sZ);

	return GetDistanceBetweenPoints3D(iX,iY,iZ,px,py,pz);
} 
 
Tryg3D::Function:: bool:IsPointBetween2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB){
	return (GetDistanceBetweenPoints2D(xA,yA,xB,yB) == (GetDistanceBetweenPoints2D(xA,yA,px,py) + GetDistanceBetweenPoints2D(xB,yB,px,py)));
} 
 
Tryg3D::Function:: bool:IsPointBetween2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB){
	return (GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB) == (GetDistanceBetweenPoints3D(xA,yA,zA,px,py,pz) + GetDistanceBetweenPoints3D(xB,yB,zB,px,py,pz)));
} 
 
//Abyss Morgan Algorithm (False Ellipse Test 2D)
Tryg3D::Function:: bool:IsPointNearly2Points2D(Float:px,Float:py,Float:xA,Float:yA,Float:xB,Float:yB,Float:maxdist){
	new Float:dAB = GetDistanceBetweenPoints2D(xA,yA,xB,yB);
	return (dAB <= (GetDistanceBetweenPoints2D(xA,yA,px,py) + GetDistanceBetweenPoints2D(xB,yB,px,py)) <= (dAB+maxdist));
} 
 
//Abyss Morgan Algorithm (False Ellipse Test 3D)
Tryg3D::Function:: bool:IsPointNearly2Points3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:maxdist){
	new Float:dAB = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	return (dAB <= (GetDistanceBetweenPoints3D(xA,yA,zA,px,py,pz) + GetDistanceBetweenPoints3D(xB,yB,zB,px,py,pz)) <= (dAB+maxdist));
} 
 
//IsPointInCylinder by Crayder
Tryg3D::Function:: bool:IsPointInCylinder3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius){
	new Float:cylinder_length = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	if(cylinder_length <= 0.0) return false;
	new Float:iX, Float:iY, Float:iZ,
		Float:distance = GetDistanceFromPointToLine(px,py,pz,xA,yA,zA,xB,yB,zB,iX,iY,iZ),
		Float:tmp_radius = (GetDistanceBetweenPoints3D(iX,iY,iZ,xA,yA,zA) / cylinder_length * radius) + (GetDistanceBetweenPoints3D(iX,iY,iZ,xB,yB,zB) / cylinder_length * radius);
	return (distance != -1.0 && distance <= tmp_radius);
}
 
 
//x,y,z - cube center point, rx,ry,rz - cube rotations
Tryg3D::Function:: bool:IsPointInCube3D(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z){
	if(size_x <= 0 || size_y <= 0 || size_z <= 0.0) return false;
	new Float:offset_x,Float:offset_y,Float:offset_z;
	size_x /= 2.0, size_y /= 2.0, size_z /= 2.0;
	ShiftPositionToOffset(x,y,z,rx,ry,rz,offset_x,offset_y,offset_z,px,py,pz);
	return IsPointInCube(offset_x,offset_y,offset_z,-size_x,-size_y,-size_z,size_x,size_y,size_z); 
} 
 
//IsPointInCone by Crayder
Tryg3D::Function:: bool:IsPointInCone3D(Float:px,Float:py,Float:pz,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius){
	new Float:cylinder_length = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB);
	if(cylinder_length <= 0.0) return false;
	new Float:iX, Float:iY, Float:iZ,
		Float:distance = GetDistanceFromPointToLine(px,py,pz,xA,yA,zA,xB,yB,zB,iX,iY,iZ),
		Float:radius = (GetDistanceBetweenPoints3D(iX,iY,iZ,xA,yA,zA) / cylinder_length * pointB_radius) + (GetDistanceBetweenPoints3D(iX,iY,iZ,xB,yB,zB) / cylinder_length * pointA_radius);
	return (distance != -1.0 && distance <= radius);
} 
 
//Abyss Morgan Algorithm Circular Sector
Tryg3D::Function:: bool:IsPointInCircularSector(Float:px,Float:py,Float:x,Float:y,Float:rz,Float:radius,Float:view_angle){
	if(GetDistanceBetweenPoints2D(px,py,x,y)-radius > (FLOAT_DEFECT*100)) return false;
	new Float:trz;
	view_angle /= 2.0;
	GetRotationFor2Point2D(x,y,px,py,trz);
	return (IsRotationTest(trz,rz-view_angle,rz+view_angle));
} 
 
//Abyss Morgan Algorithm Spherical Sector
Tryg3D::Function:: bool:IsPointInSphericalSector(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz){
	if(GetDistanceBetweenPoints3D(px,py,pz,x,y,z)-radius > (FLOAT_DEFECT*100)) return false;
	new Float:trx,Float:trz;
	vrx /= 2.0;
	vrz /= 2.0;
	if(!GetRotationFor2Point3D(x,y,z,px,py,pz,trx,trz)) return false;
	return (IsRotationTest(trx,rx-vrx,rx+vrx) && IsRotationTest(trz,rz-vrz,rz+vrz));
} 
 
//Abyss Morgan Algorithm Spherical Sector
Tryg3D::Function:: bool:IsPointInSphericalSectorEx(Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz,bool:testLOS=true){
	if(GetDistanceBetweenPoints3D(px,py,pz,x,y,z) > radius) return false;
	
	vrx /= 2.0;
	vrz /= 2.0;
	
	new Float:trx,Float:trz;
	
	#if defined Tryg3D_ColAndreas
		if(testLOS){
			new Float:xC,Float:yC,Float:zC;
			CA_RayCastLine(x,y,z,px,py,pz,xC,yC,zC);
			if(!(xC == 0.0 || yC == 0.0 || zC == 0.0)) return false;
		}
	#else
		#pragma unused testLOS
	#endif
	
	if(!GetRotationFor2Point3D(x,y,z,px,py,pz,trx,trz)) return false;
	return (IsRotationTest(trx,rx-vrx,rx+vrx) && IsRotationTest(trz,rz-vrz,rz+vrz));
} 
 
Tryg3D::Function:: bool:IsPointInEllipse(Float:px,Float:py,Float:cx,Float:cy,Float:size_x,Float:size_y){
	new Float:rz;
	GetRotationFor2Point2D(cx,cy,px,py,rz);
	return (GetDistanceBetweenPoints2D(px,py,cx,cy) <= GetEllipseRadius(size_x,size_y,rz));
} 
 
Tryg3D::Function:: bool:IsPointInEllipticalCylinder2D(Float:px,Float:py,Float:pz,Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y){
	if(!((pz >= minz) && (pz <= maxz))) return false;
	new Float:rz;
	GetRotationFor2Point2D(cx,cy,px,py,rz);
	return (GetDistanceBetweenPoints2D(px,py,cx,cy) <= GetEllipseRadius(size_x,size_y,rz));
} 
 
//Polygon Test by RyDeR SRC:http://forum.sa-mp.com/showpost.php?p=1154971&postcount=1871 (Updated)
Tryg3D::Function:: bool:IsPointInPolygon(Float:x,Float:y,Float:points[],maxpoints = sizeof(points)){
	new polygon_Sides = ((maxpoints - 2) / 2);
	if((maxpoints - 2) & 0b1 || polygon_Sides < 3) return false;
	
	new Float:polygon_Data[2][MAX_POLYGON_POINTS], cross_Total;
	
	for(new i = 0, j; i < maxpoints; i += 2, j++){
		polygon_Data[0][j] = points[i];
		polygon_Data[1][j] = points[i+1];
	}
	for(new i, j = polygon_Sides - 1; i < polygon_Sides; j = i, i++){
		if(polygon_Data[1][i] < y && polygon_Data[1][j] >= y || polygon_Data[1][j] < y && polygon_Data[1][i] >= y){
			if(polygon_Data[0][i] + (y - polygon_Data[1][i]) / (polygon_Data[1][j] - polygon_Data[1][i]) * (polygon_Data[0][j] - polygon_Data[0][i]) < x){
				cross_Total++;
			}
		}
	}
	return bool:(cross_Total & 0x1);
} 
 
//GetRandomPointInCircle by Crayder
Tryg3D::Function:: GetRandomPointInCircle(Float:x,Float:y,Float:radius,&Float:tx,&Float:ty){
	//"float(random(1000001)) / 1000000.0" is RandomFloat for 0.0 - 1.0.
	new Float:T3D:alfa = float(random(1000001))/1000000.0,
		Float:T3D:beta = float(random(1000001))/1000000.0;
	if(T3D:beta < T3D:alfa) Tryg3D::SwapInt(T3D:alfa,T3D:beta);
	tx = x + (T3D:beta * radius * floatcos(2.0 * FLOAT_PI * T3D:alfa / T3D:beta));
	ty = y + (T3D:beta * radius * floatsin(2.0 * FLOAT_PI * T3D:alfa / T3D:beta));
} 
 
//GetRandomPointInCylinder2D by Crayder
Tryg3D::Function:: GetRandomPointInCylinder2D(Float:x,Float:y,Float:minz,Float:maxz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	GetRandomPointInCircle(x,y,radius,tx,ty);
	tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)))+minz;
} 
 
//GetRandomPointInCylinder3D by Abyss Morgan
Tryg3D::Function:: GetRandomPointInCylinder3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	new Float:px,Float:py,Float:pz,Float:trx,Float:trz;
	GetRotationFor2Point3D(xA,yA,zA,xB,yB,zB,trx,trz);
	GetPointInFront3D(xA,yA,zA,trx,trz,RandomFloat(0.0,GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB)),px,py,pz);
	GetPointInFront3DEx(px,py,pz,RandomFloat(0.0,360.0),trx,CompRotationFloat(trz+90.0),RandomFloat(0.0,radius),tx,ty,tz);
} 
 
Tryg3D::Function:: GetRandomPointInSphere(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	GetPointInFront3D(x,y,z,RandomFloat(0.0,360.0),RandomFloat(0.0,360.0),RandomFloat(0.0,radius),tx,ty,tz);
} 
 
Tryg3D::Function:: GetRandomPointInRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy,&Float:tx,&Float:ty){
	tx = RandomFloat(0.0,floatsqroot(floatpower(minx-maxx,2)),6)+minx;
	ty = RandomFloat(0.0,floatsqroot(floatpower(miny-maxy,2)),6)+miny;
} 
 
Tryg3D::Function:: GetRandomPointInCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:tx,&Float:ty,&Float:tz){
	tx = RandomFloat(0.0,floatsqroot(floatpower(minx-maxx,2)),6)+minx;
	ty = RandomFloat(0.0,floatsqroot(floatpower(miny-maxy,2)),6)+miny;
	tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)),6)+minz;
} 
 
Tryg3D::Function:: GetRandomPointInCube3D(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z,&Float:tx,&Float:ty,&Float:tz){
	if(size_x <= 0 || size_y <= 0 || size_z <= 0.0) return 0;
	new Float:offset_x,Float:offset_y,Float:offset_z;
	size_x /= 2.0, size_y /= 2.0, size_z /= 2.0;
	GetRandomPointInCube(-size_x,-size_y,-size_z,size_x,size_y,size_z,offset_x,offset_y,offset_z);
	ShiftOffsetToPosition(x,y,z,rx,ry,rz,offset_x,offset_y,offset_z,tx,ty,tz);
	return 1;
} 
 
//GetRandomPointInCone3D by Abyss Morgan
Tryg3D::Function:: GetRandomPointInCone3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius,&Float:tx,&Float:ty,&Float:tz){
	new Float:px,Float:py,Float:pz,Float:trx,Float:trz,
		Float:dist = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB),
		Float:rand_dist = RandomFloat(0.0,dist),
		Float:radius = rand_dist*((pointB_radius-pointA_radius)*(1.0/dist))+pointA_radius;
	GetRotationFor2Point3D(xA,yA,zA,xB,yB,zB,trx,trz);
	GetPointInFront3D(xA,yA,zA,trx,trz,rand_dist,px,py,pz);
	GetPointInFront3DEx(px,py,pz,RandomFloat(0.0,360.0),trx,CompRotationFloat(trz+90.0),RandomFloat(0.0,radius),tx,ty,tz);
} 
 
Tryg3D::Function:: GetRandomPointInCircularSector(Float:x,Float:y,Float:rz,Float:radius,Float:view_angle,&Float:tx,&Float:ty){
	view_angle /= 2.0;
	new Float:rand_rz = CompRotationFloat(RandomFloat(rz-view_angle+360.0,rz+view_angle+360.0,6)),
		Float:rand_rad = RandomFloat(FLOAT_DEFECT*100.0,radius,6);
	if(rand_rad > radius) rand_rad = radius;
	rand_rz = NMTV(rand_rz,(rz+view_angle));
	rand_rz = NLTV(rand_rz,(rz-view_angle));
	GetPointInFront2D(x,y,rand_rz,rand_rad,tx,ty);
} 
 
//Beta Algorithm by Abyss Morgan
Tryg3D::Function:: GetRandomPointInSphericalSector(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz,&Float:tx,&Float:ty,&Float:tz){
	new Float:rand_rx = CompRotationFloat(RandomFloat(rx-vrx+360.0,rx+vrx+360.0,6)),
		Float:rand_rz = CompRotationFloat(RandomFloat(rz-vrz+360.0,rz+vrz+360.0,6)),
		Float:rand_rad = RandomFloat(FLOAT_DEFECT*100.0,radius,6);
		
	vrx /= 2.0;
	vrz /= 2.0;

	if(rand_rad > radius) rand_rad = radius;
	
	if(rand_rx > rx+vrx) rand_rx = rx+vrx;
	if(rand_rx < rx-vrx) rand_rx = rx-vrx;
	
	if(rand_rz > rz+vrz) rand_rz = rz+vrz;
	if(rand_rz < rz-vrz) rand_rz = rz-vrz;
	
	GetPointInFront3D(x,y,z,rand_rx,rand_rz,rand_rad,tx,ty,tz);
} 
 
Tryg3D::Function:: GetRandomPointInEllipse(Float:cx,Float:cy,Float:size_x,Float:size_y,&Float:tx,&Float:ty){
	new Float:omega = RandomFloat(0.0,360.0,6);
	GetPointInFront2D(cx,cy,omega,RandomFloat(0.0,GetEllipseRadius(size_x,size_y,omega),6),tx,ty);
} 
 
Tryg3D::Function:: GetRandomPointInEllipticalCyl2D(Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y,&Float:tx,&Float:ty,&Float:tz){
	new Float:omega = RandomFloat(0.0,360.0,6);
	GetPointInFront2D(cx,cy,omega,RandomFloat(0.0,GetEllipseRadius(size_x,size_y,omega),6),tx,ty);
	tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)),6)+minz;
} 
 
//Abyss Morgan Algorithm Polygon
Tryg3D::Function:: GetRandomPointInPolygon(Float:points[],&Float:tx,&Float:ty,maxpoints = sizeof(points)){
	new Float:minx, Float:miny, Float:maxx, Float:maxy, recheck = 1;
	
	minx = maxx = points[0];
	miny = maxy = points[1];
	
	for(new i = 2; i < maxpoints; i += 2){
		if(points[i] < minx)	minx = points[i];
		if(points[i] > maxx)	maxx = points[i];
		if(points[i+1] < miny) 	miny = points[i+1];
		if(points[i+1] > maxy)	maxy = points[i+1];
	}
	
	GetRandomPointInRectangle(minx,miny,maxx,maxy,tx,ty);
	while(!IsPointInPolygon(tx,ty,points,maxpoints)){
		GetRandomPointInRectangle(minx,miny,maxx,maxy,tx,ty);
		recheck++;
	}
	
	return recheck;
} 
 
Tryg3D::Function:: Float:GetRandomPointOnClock(Float:x,Float:y,Float:radius,&Float:tx,&Float:ty,&Float:trz,Float:rz = INVALID_ROTATION){
	if(rz == INVALID_ROTATION) rz = RandomFloat(0.0,360.0);
	GetPointInFront2D(x,y,rz,radius,tx,ty);
	return CompRotationFloat(rz-180.0,trz);
} 
 
Tryg3D::Function:: GetRandomPointOnCylinder2D(Float:x,Float:y,Float:minz,Float:maxz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	GetRandomPointOnCircle(x,y,radius,tx,ty);
	tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)))+minz;
} 
 
//GetRandomPointOnCylinder3D by Abyss Morgan
Tryg3D::Function:: GetRandomPointOnCylinder3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	new Float:px,Float:py,Float:pz,Float:trx,Float:trz;
	GetRotationFor2Point3D(xA,yA,zA,xB,yB,zB,trx,trz);
	GetPointInFront3D(xA,yA,zA,trx,trz,RandomFloat(0.0,GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB)),px,py,pz);
	GetPointInFront3DEx(px,py,pz,RandomFloat(0.0,360.0),trx,CompRotationFloat(trz+90.0),radius,tx,ty,tz);
} 
 
//GetRandomPointOnSphere by Neil Lamoureux
Tryg3D::Function:: GetRandomPointOnSphere(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	new Float:T3D:alfa = float(random(1000001))/1000000.0,
		Float:T3D:beta = float(random(1000001))/1000000.0,
		Float:T3D:theta = 2 * FLOAT_PI * T3D:alfa,
		Float:T3D:phi = acos(2 * T3D:beta - 1);
	tx = x + (radius * floatsin(T3D:phi,degrees) * floatcos(T3D:theta,degrees));
	ty = y + (radius * floatsin(T3D:phi,degrees) * floatsin(T3D:theta,degrees));
	tz = z + (radius * floatcos(T3D:phi,degrees));
} 
 
Tryg3D::Function:: GetRandomPointOnRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy,&Float:tx,&Float:ty){
	switch(random(4)){
		case 0: {
			tx = minx;
			ty = RandomFloat(0.0,floatsqroot(floatpower(miny-maxy,2)),6)+miny;
		}
		case 1: {
			tx = maxx;
			ty = RandomFloat(0.0,floatsqroot(floatpower(miny-maxy,2)),6)+miny;
		}
		case 2: {
			tx = RandomFloat(0.0,floatsqroot(floatpower(minx-maxx,2)),6)+minx;
			ty = miny;
		}
		case 3: {
			tx = RandomFloat(0.0,floatsqroot(floatpower(minx-maxx,2)),6)+minx;
			ty = maxy;
		}
	}
} 
 
Tryg3D::Function:: GetRandomPointOnCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz,&Float:tx,&Float:ty,&Float:tz){
	switch(random(12)){
		case 0: {
			tx = minx;
			ty = RandomFloat(0.0,floatsqroot(floatpower(miny-maxy,2)),6)+miny;
			tz = minz;
		}
		case 1: {
			tx = maxx;
			ty = RandomFloat(0.0,floatsqroot(floatpower(miny-maxy,2)),6)+miny;
			tz = minz;
		}
		case 2: {
			tx = RandomFloat(0.0,floatsqroot(floatpower(minx-maxx,2)),6)+minx;
			ty = miny;
			tz = minz;
		}
		case 3: {
			tx = RandomFloat(0.0,floatsqroot(floatpower(minx-maxx,2)),6)+minx;
			ty = maxy;
			tz = minz;
		}
		case 4: {
			tx = minx;
			ty = RandomFloat(0.0,floatsqroot(floatpower(miny-maxy,2)),6)+miny;
			tz = maxz;
		}
		case 5: {
			tx = maxx;
			ty = RandomFloat(0.0,floatsqroot(floatpower(miny-maxy,2)),6)+miny;
			tz = maxz;
		}
		case 6: {
			tx = RandomFloat(0.0,floatsqroot(floatpower(minx-maxx,2)),6)+minx;
			ty = miny;
			tz = maxz;
		}
		case 7: {
			tx = RandomFloat(0.0,floatsqroot(floatpower(minx-maxx,2)),6)+minx;
			ty = maxy;
			tz = maxz;
		}
		case 8: {
			tx = minx;
			ty = miny;
			tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)),6)+minz;
		}
		case 9: {
			tx = maxx;
			ty = miny;
			tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)),6)+minz;
		}
		case 10: {
			tx = minx;
			ty = maxy;
			tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)),6)+minz;
		}
		case 11: {
			tx = maxx;
			ty = maxy;
			tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)),6)+minz;
		}
	}
} 
 
Tryg3D::Function:: GetRandomPointOnCube3D(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z,&Float:tx,&Float:ty,&Float:tz){
	if(size_x <= 0 || size_y <= 0 || size_z <= 0.0) return 0;
	new Float:offset_x,Float:offset_y,Float:offset_z;
	size_x /= 2.0, size_y /= 2.0, size_z /= 2.0;
	GetRandomPointOnCube(-size_x,-size_y,-size_z,size_x,size_y,size_z,offset_x,offset_y,offset_z);
	ShiftOffsetToPosition(x,y,z,rx,ry,rz,offset_x,offset_y,offset_z,tx,ty,tz);
	return 1;
} 
 
//GetRandomPointOnCone3D by Abyss Morgan
Tryg3D::Function:: GetRandomPointOnCone3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius,&Float:tx,&Float:ty,&Float:tz){
	new Float:px,Float:py,Float:pz,Float:trx,Float:trz,
		Float:dist = GetDistanceBetweenPoints3D(xA,yA,zA,xB,yB,zB),
		Float:rand_dist = RandomFloat(0.0,dist),
		Float:radius = rand_dist*((pointB_radius-pointA_radius)*(1.0/dist))+pointA_radius;
	GetRotationFor2Point3D(xA,yA,zA,xB,yB,zB,trx,trz);
	GetPointInFront3D(xA,yA,zA,trx,trz,rand_dist,px,py,pz);
	GetPointInFront3DEx(px,py,pz,RandomFloat(0.0,360.0),trx,CompRotationFloat(trz+90.0),radius,tx,ty,tz);
} 
 
Tryg3D::Function:: GetRandomPointOnCircularSector(Float:x,Float:y,Float:rz,Float:radius,Float:view_angle,&Float:tx,&Float:ty){
	view_angle /= 2.0;
	new Float:rand_rz = CompRotationFloat(RandomFloat(rz-view_angle+360.0,rz+view_angle+360.0,6));
	rand_rz = NMTV(rand_rz,(rz+view_angle));
	rand_rz = NLTV(rand_rz,(rz-view_angle));
	GetPointInFront2D(x,y,rand_rz,radius,tx,ty);
} 
 
//Beta Algorithm by Abyss Morgan
Tryg3D::Function:: GetRandomPointOnSphericalSector(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz,&Float:tx,&Float:ty,&Float:tz){
	vrx /= 2.0;
	vrz /= 2.0;
	new Float:rand_rx = CompRotationFloat(RandomFloat(rx-vrx+360.0,rx+vrx+360.0,6)),
		Float:rand_rz = CompRotationFloat(RandomFloat(rz-vrz+360.0,rz+vrz+360.0,6));
	
	if(rand_rx > rx+vrx) rand_rx = rx+vrx;
	if(rand_rx < rx-vrx) rand_rx = rx-vrx;
	
	if(rand_rz > rz+vrz) rand_rz = rz+vrz;
	if(rand_rz < rz-vrz) rand_rz = rz-vrz;
	
	GetPointInFront3D(x,y,z,rand_rx,rand_rz,radius,tx,ty,tz);
} 
 
Tryg3D::Function:: GetRandomPointOnEllipse(Float:cx,Float:cy,Float:size_x,Float:size_y,&Float:tx,&Float:ty){
	new Float:omega = RandomFloat(0.0,360.0,6);
	GetPointInFront2D(cx,cy,omega,GetEllipseRadius(size_x,size_y,omega),tx,ty);
} 
 
Tryg3D::Function:: GetRandomPointOnEllipticalCyl2D(Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y,&Float:tx,&Float:ty,&Float:tz){
	new Float:omega = RandomFloat(0.0,360.0,6);
	GetPointInFront2D(cx,cy,omega,GetEllipseRadius(size_x,size_y,omega),tx,ty);
	tz = RandomFloat(0.0,floatsqroot(floatpower(minz-maxz,2)),6)+minz;
} 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Universal Functions                                                                                                              *
 *                                                                                                                                  *
 ************************************************************************************************************************************/ 
 
Tryg3D::Function:: bool:GetElementPos(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,&Float:x,&Float:y,&Float:z){
	switch(element_type){
		case item_player: {
			GetPlayerPos(_:elementid,x,y,z);
		}
		case item_npc: {
			#if defined Tryg3D_FCNPC
				if(FCNPC_IsValid(_:elementid)){
					FCNPC_GetPosition(_:elementid,x,y,z);
				} else {
					GetPlayerPos(_:elementid,x,y,z);
				}
			#else
				GetPlayerPos(_:elementid,x,y,z);
			#endif
		}
		#if defined Tryg3D_Actor
			case item_actor: {
				GetActorPos(_:elementid,x,y,z);
			}
		#endif
		case item_object: {
			GetObjectPos(_:elementid,x,y,z);
		}
		case item_vehicle: {
			GetVehiclePos(_:elementid,x,y,z);
		}
		
		#if defined Tryg3D_Streamer
			case item_dynamic_object: {
				GetDynamicObjectPos(STREAMER_TAG_OBJECT (_:elementid),x,y,z);
			}
			case item_dynamic_pickup: {
				Streamer_GetFloatData(STREAMER_TYPE_PICKUP,_:elementid,E_STREAMER_X,x);
				Streamer_GetFloatData(STREAMER_TYPE_PICKUP,_:elementid,E_STREAMER_Y,y);
				Streamer_GetFloatData(STREAMER_TYPE_PICKUP,_:elementid,E_STREAMER_Z,z);
			}
			case item_dynamic_cp: {
				Streamer_GetFloatData(STREAMER_TYPE_CP,_:elementid,E_STREAMER_X,x);
				Streamer_GetFloatData(STREAMER_TYPE_CP,_:elementid,E_STREAMER_Y,y);
				Streamer_GetFloatData(STREAMER_TYPE_CP,_:elementid,E_STREAMER_Z,z);
			}
			case item_dynamic_racecp: {
				Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,_:elementid,E_STREAMER_X,x);
				Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,_:elementid,E_STREAMER_Y,y);
				Streamer_GetFloatData(STREAMER_TYPE_RACE_CP,_:elementid,E_STREAMER_Z,z);
			}
			case item_dynamic_mapicon: {
				Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,_:elementid,E_STREAMER_X,x);
				Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,_:elementid,E_STREAMER_Y,y);
				Streamer_GetFloatData(STREAMER_TYPE_MAP_ICON,_:elementid,E_STREAMER_Z,z);
			}
			case item_dynamic_3dtext: {
				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,_:elementid,E_STREAMER_X,x);
				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,_:elementid,E_STREAMER_Y,y);
				Streamer_GetFloatData(STREAMER_TYPE_3D_TEXT_LABEL,_:elementid,E_STREAMER_Z,z);
			}
			case item_dynamic_actor: {
				GetDynamicActorPos(STREAMER_TAG_ACTOR (_:elementid),x,y,z);
			}
		#endif
		default: return false;
	}
	return true;
}
 
 
Tryg3D::Function:: bool:GetElementRotationQuat(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,&Float:qw,&Float:qx,&Float:qy,&Float:qz){
	new Float:rx,Float:ry,Float:rz;
	qw = qx = qy = qz = 0.0;
	switch(element_type){
		#if defined Tryg3D_YSF
			case item_player: {
				GetPlayerRotationQuat(_:elementid,qw,qx,qy,qz);
			}
		#endif
		case item_npc: {
			#if defined Tryg3D_FCNPC
				if(FCNPC_IsValid(_:elementid)){
					FCNPC_GetQuaternion(_:elementid,qw,qx,qy,qz);
					return true;
				}
			#endif
			return false;
		}
		case item_object: {
			GetObjectRot(_:elementid,rx,ry,rz);
			Tryg3D::EulerToQuat(rx,ry,rz,qw,qx,qy,qz);
			qw *= (-1);
		}
		case item_vehicle: {
			GetVehicleRotationQuat(_:elementid,qw,qx,qy,qz);
		}
		#if defined Tryg3D_Streamer
			case item_dynamic_object: {
				GetDynamicObjectRot(STREAMER_TAG_OBJECT (_:elementid),rx,ry,rz);
				Tryg3D::EulerToQuat(rx,ry,rz,qw,qx,qy,qz);
				qw *= (-1);
			}
		#endif
		default: return false;
	}
	return true;
} 
 
Tryg3D::Function:: bool:GetElementUpVector(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,&Float:vx,&Float:vy,&Float:vz){
	new Float:qw,Float:qx,Float:qy,Float:qz;
	if(!GetElementRotationQuat(elementid,element_type,qw,qx,qy,qz)) return false;
	
	switch(element_type){
		case item_object: {
			GetQuatUpVector(qw,qx,qy,qz,vx,vy,vz);
		}
		case item_vehicle: {
			GetQuatUpVector(qw,-qx,-qy,-qz,vx,vy,vz);
		}
		#if defined Tryg3D_Streamer
			case item_dynamic_object: {
				GetQuatUpVector(qw,qx,qy,qz,vx,vy,vz);
			}
		#endif
		default: return false;
	}
	return true;
} 
 
Tryg3D::Function:: bool:GetElementUpPos(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:radius,&Float:x,&Float:y,&Float:z,bool:reverse=false){
	new Float:vx,Float:vy,Float:vz,Float:rx,Float:rz;
	if(!GetElementUpVector(elementid,element_type,vx,vy,vz)) return false;
	ShiftVectorToRotation(vx,vy,vz,rx,rz);
	if(!GetElementPos(elementid,element_type,vx,vy,vz)) return false;
	if(!reverse){
		GetPointInFront3D(vx,vy,vz,rx,rz,radius,x,y,z);
	} else {
		GetPointInFront3D(vx,vy,vz,CompRotationFloat(rx-180.0),rz,radius,x,y,z);
	}
	return true;
} 
 
Tryg3D::Function:: bool:IsElementOnPlayerScreen(playerid,TRYG3D_ELEMENT_TAG targetid,Item3D_Type:target_type=item_player,element_orientation:orientation=o_front,Float:rx=INVALID_ROTATION,Float:rz=INVALID_ROTATION,Float:vrx=VERTICAL_CAMERA_RADIUS,Float:vrz=HORIZONTAL_CAMERA_RADIUS,bool:testLOS=true,bool:testVW=true){
	new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:prx,Float:prz,worldid;
	GetPlayerCameraPos(playerid,x,y,z);
	GetPlayerCameraRotation(playerid,prx,prz);
	
	switch(orientation){
		case o_left:	prx = CompRotationFloat(prx+90.0);
		case o_right:	prx = CompRotationFloat(prx-90.0);
		case o_back:	prx = CompRotationFloat(prx+180.0);
	}
	
	worldid = GetPlayerVirtualWorld(playerid);
	if(rx != INVALID_ROTATION) prx = rx;
	if(rz != INVALID_ROTATION) prz = rz;
	
	if(!GetElementPos(targetid,target_type,tx,ty,tz)) return false;
	
	switch(target_type){
		case item_player: {
			if(testVW && worldid != GetPlayerVirtualWorld(_:targetid)) return false;
		}
		case item_npc: {
			#if defined Tryg3D_FCNPC
				if(FCNPC_IsValid(_:targetid)){
					if(testVW && worldid != FCNPC_GetVirtualWorld(_:targetid)) return false;
				} else {
					if(testVW && worldid != GetPlayerVirtualWorld(_:targetid)) return false;
				}
			#else
				if(testVW && worldid != GetPlayerVirtualWorld(_:targetid)) return false;
			#endif
		}
		#if defined Tryg3D_Actor
			case item_actor: {
				if(testVW && worldid != GetActorVirtualWorld(_:targetid)) return false;
			}
		#endif
		case item_vehicle: {
			if(testVW && worldid != GetVehicleVirtualWorld(_:targetid)) return false;
		}
		#if defined Tryg3D_Streamer
			case item_dynamic_object: {
				if(testVW && worldid != Streamer_GetIntData(STREAMER_TYPE_OBJECT,_:targetid,E_STREAMER_WORLD_ID)) return false;
			}
			case item_dynamic_pickup: {
				if(testVW && worldid != Streamer_GetIntData(STREAMER_TYPE_PICKUP,_:targetid,E_STREAMER_WORLD_ID)) return false;
			}
			case item_dynamic_cp: {
				if(testVW && worldid != Streamer_GetIntData(STREAMER_TYPE_CP,_:targetid,E_STREAMER_WORLD_ID)) return false;
			}
			case item_dynamic_racecp: {
				if(testVW && worldid != Streamer_GetIntData(STREAMER_TYPE_RACE_CP,_:targetid,E_STREAMER_WORLD_ID)) return false;
			}
			case item_dynamic_mapicon: {
				if(testVW && worldid != Streamer_GetIntData(STREAMER_TYPE_MAP_ICON,_:targetid,E_STREAMER_WORLD_ID)) return false;
			}
			case item_dynamic_3dtext: {
				if(testVW && worldid != Streamer_GetIntData(STREAMER_TYPE_3D_TEXT_LABEL,_:targetid,E_STREAMER_WORLD_ID)) return false;
			}
			case item_dynamic_actor: {
				if(testVW && worldid != GetDynamicActorVirtualWorld(STREAMER_TAG_ACTOR (_:targetid))) return false;
			}
		#endif
		default: return false;
	}
	return IsPointInSphericalSectorEx(tx,ty,tz,x,y,z,prx,prz,Tryg3D::StreamDistance,vrx,vrz,testLOS);
} 
 
Tryg3D::Function:: bool:IsElementOnFakeScreen(Float:x,Float:y,Float:z,TRYG3D_ELEMENT_TAG targetid,Item3D_Type:target_type,Float:rx,Float:rz,Float:vrx=VERTICAL_CAMERA_RADIUS,Float:vrz=HORIZONTAL_CAMERA_RADIUS,bool:testLOS=true){
	new Float:tx,Float:ty,Float:tz;
	if(!GetElementPos(targetid,target_type,tx,ty,tz)) return false;
	return IsPointInSphericalSectorEx(tx,ty,tz,x,y,z,rx,rz,Tryg3D::StreamDistance,vrx,vrz,testLOS);
} 
 
Tryg3D::Function:: Float:GetElementsDistance(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,TRYG3D_ELEMENT_TAG targetid,Item3D_Type:target_type){
	new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz;
	if(!GetElementPos(elementid,element_type,x,y,z)) return -1.0;
	if(!GetElementPos(targetid,target_type,tx,ty,tz)) return -1.0;
	return GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
} 
 
Tryg3D::Function:: Float:GetElementDistanceFromPoint(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:x,Float:y,Float:z){
	new Float:tx,Float:ty,Float:tz;
	if(!GetElementPos(elementid,element_type,tx,ty,tz)) return -1.0;
	return GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz);
} 
 
Tryg3D::Function:: bool:IsElementInCircle(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:x,Float:y,Float:radius){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInCircle(px,py,x,y,radius);
} 
 
Tryg3D::Function:: bool:IsElementInCylinder3D(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInCylinder3D(px,py,pz,xA,yA,zA,xB,yB,zB,radius);
} 
 
Tryg3D::Function:: bool:IsElementInCylinder2D(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:x,Float:y,Float:minz,Float:maxz,Float:radius){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInCylinder2D(px,py,pz,x,y,minz,maxz,radius);
}
 
 
Tryg3D::Function:: bool:IsElementInSphere(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:x,Float:y,Float:z,Float:radius){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInSphere(px,py,pz,x,y,z,radius);
} 
 
Tryg3D::Function:: bool:IsElementInRectangle(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:minx,Float:miny,Float:maxx,Float:maxy){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInRectangle(px,py,minx,miny,maxx,maxy);
} 
 
Tryg3D::Function:: bool:IsElementInCube(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInCube(px,py,pz,minx,miny,minz,maxx,maxy,maxz);
} 
 
Tryg3D::Function:: bool:IsElementInPolygon(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:points[],maxpoints = sizeof(points)){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInPolygon(px,py,points,maxpoints);
} 
 
Tryg3D::Function:: bool:IsElementInCircularSector(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:x,Float:y,Float:rz,Float:radius,Float:view_angle){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInCircularSector(px,py,x,y,rz,radius,view_angle);
} 
 
Tryg3D::Function:: bool:IsElementInSphericalSector(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInSphericalSector(px,py,pz,x,y,z,rx,rz,radius,vrx,vrz);
}
 
 
Tryg3D::Function:: bool:IsElementInCone(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInCone3D(px,py,pz,xA,yA,zA,xB,yB,zB,pointA_radius,pointB_radius);
} 
 
Tryg3D::Function:: bool:IsElementInCube3D(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInCube3D(px,py,pz,x,y,z,rx,ry,rz,size_x,size_y,size_z);
} 
 
Tryg3D::Function:: bool:IsElementInEllipse(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:cx,Float:cy,Float:size_x,Float:size_y){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInEllipse(px,py,cx,cy,size_x,size_y);
} 
 
Tryg3D::Function:: bool:IsElementInEllipticalCylinder2D(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInEllipticalCylinder2D(px,py,pz,cx,cy,minz,maxz,size_x,size_y);
} 
 
Tryg3D::Function:: bool:GetElementToPointVector(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:tx,Float:ty,Float:tz,&Float:vx,&Float:vy,&Float:vz){
	new Float:px,Float:py,Float:pz,Float:rx,Float:rz;
	if(!GetElementPos(elementid,element_type,px,py,pz)) return false;
	if(GetRotationFor2Point3D(px,py,pz,tx,ty,tz,rx,rz)){
		ShiftRotationToVector(rx,rz,vx,vy,vz);
		return true;
	} else {
		vx = vy = vz = 0.0;
		return false;
	}
} 
 
Tryg3D::Function:: bool:GetElementRotatedVector(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:tx,Float:ty,Float:tz,&Float:vx,&Float:vy,&Float:vz,bool:return_vector=true,Float:rx=0.0,Float:ry=0.0,Float:rz=0.0){
	new Float:px,Float:py,Float:pz;
	if(!GetElementPos(elementid,element_type,px,py,pz)) return false;
	if(return_vector){
		ShiftLineRotationVector(px,py,pz,tx,ty,tz,rx,ry,rz,vx,vy,vz);
	} else {
		ShiftLineRotation(px,py,pz,tx,ty,tz,rx,ry,rz,vx,vy,vz);
	}
	return true;
} 
 
Tryg3D::Function:: bool:GetElementOrientationPos(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
	new Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz;
	if(!GetElementPos(elementid,element_type,x,y,z)) return false;
	switch(element_type){
		case item_player: {
			GetPlayerFacingAngle(_:elementid,rz);
		}
		case item_npc: {
			#if defined Tryg3D_FCNPC
				if(FCNPC_IsValid(_:elementid)){
					rz = FCNPC_GetAngle(_:elementid);
				} else {
					GetPlayerFacingAngle(_:elementid,rz);
				}
			#else
				GetPlayerFacingAngle(_:elementid,rz);
			#endif
		}
		#if defined Tryg3D_Actor
			case item_actor: {
				GetActorFacingAngle(_:elementid,rz);
			}
		#endif
		case item_object: {
			GetObjectRot(_:elementid,rx,ry,rz);
		}
		case item_vehicle: {
			Tryg3D::GetVehicleRotation(_:elementid,rx,ry,rz);
		}
		#if defined Tryg3D_Streamer
			case item_dynamic_object: {
				GetDynamicObjectRot(STREAMER_TAG_OBJECT (_:elementid),rx,ry,rz);
			}
			case item_dynamic_actor: {
				GetDynamicActorFacingAngle(STREAMER_TAG_ACTOR (_:elementid),rz);
			}
		#endif
		default: return false;
	}
	
	switch(element_type){
		case item_player, item_npc, item_actor, item_dynamic_actor: {
			switch(orientation){
				case o_left:	GetPointInFront3D(x,y,z,0.0,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				case o_right:	GetPointInFront3D(x,y,z,0.0,CompRotationFloat(rz-90.0),distance,tx,ty,tz);
				case o_up:		tx = x, ty = y, tz = z + distance;
				case o_down:	tx = x, ty = y, tz = z - distance;
				case o_front:	GetPointInFront3D(x,y,z,0.0,rz,distance,tx,ty,tz);
				case o_back:	GetPointInFront3D(x,y,z,0.0,CompRotationFloat(rz+180.0),distance,tx,ty,tz);
			}
		}
		case item_vehicle, item_object, item_dynamic_object: {
			switch(orientation){
				case o_left:	GetPointInFront3D(x,y,z,ry,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				case o_right:	GetPointInFront3D(x,y,z,CompRotationFloat(ry+180.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				case o_up:		GetElementUpPos(elementid,element_type,distance,tx,ty,tz);
				case o_down:	GetElementUpPos(elementid,element_type,distance,tx,ty,tz,true);
				case o_front:	GetPointInFront3D(x,y,z,rx,rz,distance,tx,ty,tz);
				case o_back:	GetPointInFront3D(x,y,z,CompRotationFloat(rx+180.0),rz,distance,tx,ty,tz);
			}
		}
	}
	return true;
} 
 
#if defined Tryg3D_Anims 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Animation Functions                                                                                                              *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
  
 
Tryg3D::Function:: bool:IsPlayerSkydiving(playerid){
	new T3D:index = GetPlayerAnimationIndex(playerid);
	return (T3D:index >= 958 && T3D:index <= 962);
} 
 
Tryg3D::Function:: bool:IsPlayerUsingParachute(playerid){
	new T3D:index = GetPlayerAnimationIndex(playerid);
	return (T3D:index >= 963 && T3D:index <= 979);
} 
 
Tryg3D::Function:: bool:IsPlayerAiming(playerid){
	switch(GetPlayerAnimationIndex(playerid)){
		case 1160..1163,1167,1365,1643,1453,220: return true;
	}
	return false;
} 
 
Tryg3D::Function:: bool:IsPlayerStay(playerid){
	new T3D:index = GetPlayerAnimationIndex(playerid);
	return (T3D:index == 1189 || T3D:index == 1133);
} 
 
Tryg3D::Function:: bool:IsPlayerRunning(playerid){
	new T3D:index = GetPlayerAnimationIndex(playerid);
	return (T3D:index == 1231 || T3D:index == 1266 || T3D:index == 1196);
} 
 
Tryg3D::Function:: bool:IsPlayerSwim(playerid){
	new T3D:index = GetPlayerAnimationIndex(playerid);
	return (T3D:index == 1538 || T3D:index == 1539 || T3D:index == 1541 || T3D:index == 1544);
} 
 
Tryg3D::Function:: bool:IsPlayerJump(playerid){
	new T3D:index = GetPlayerAnimationIndex(playerid);
	return (T3D:index == 1195 || T3D:index == 1198);
} 
 
Tryg3D::Function:: bool:IsPlayerParaFall(playerid){
	new T3D:index = GetPlayerAnimationIndex(playerid);
	return (T3D:index == 958 || T3D:index == 959 || T3D:index == 961 || T3D:index == 962 || T3D:index == 1134);
}
 
 
Tryg3D::Function:: bool:IsPlayerParaGlide(playerid){
	new T3D:index = GetPlayerAnimationIndex(playerid);
	return (T3D:index == 963 || T3D:index == 965 || T3D:index == 971 || T3D:index == 976 || T3D:index == 978);
} 
 
Tryg3D::Function:: bool:IsPlayerFall(playerid){
	return (GetPlayerAnimationIndex(playerid) == 1130);
} 
 
#endif 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Extended Functions                                                                                                               *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

 //flag_a
#define Tryg3D_GetActiveCount() 						GetSVarInt("ADM:3DTryg:ACTIVE")
#define Tryg3D_GetErrorCount() 							GetSVarInt("ADM:3DTryg:Error")
#define Tryg3D_ResetErrorCount() 						SetSVarInt("ADM:3DTryg:Error",0)
#define Update3DTrygErrorCount() 						SetSVarInt("ADM:3DTryg:Error",Tryg3D::GetErrorCount()+1)

#define Tryg3D_SetStreamDistance(%0)					Tryg3D::StreamDistance = (%0)
#define Tryg3D_GetStreamDistance()						Tryg3D::StreamDistance 
 
Tryg3D::Function:: Tryg3D::GetModules(&modules_count=0){
	modules_count = 0;
	new T3D:string[128];
	#if (defined Tryg3D_YSF && defined ENABLE_3D_TRYG_TIMELINE_SYNC)
		format(T3D:string,sizeof(T3D:string),"4D");
	#else
		format(T3D:string,sizeof(T3D:string),"3D");
	#endif
	
	#if defined Tryg3D_MapAndreas
		format(T3D:string,sizeof(T3D:string),"%s:MapAndreas",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_ColAndreas
		format(T3D:string,sizeof(T3D:string),"%s:ColAndreas",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_YSF
		format(T3D:string,sizeof(T3D:string),"%s:YSF",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_Streamer
		format(T3D:string,sizeof(T3D:string),"%s:Streamer",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_FoxForeach
		format(T3D:string,sizeof(T3D:string),"%s:FoxForeach",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_YSIForeach
		format(T3D:string,sizeof(T3D:string),"%s:YSIForeach",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_FCNPC
		format(T3D:string,sizeof(T3D:string),"%s:FCNPC",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_Stream3D
		format(T3D:string,sizeof(T3D:string),"%s:Stream3D",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_Line3D
		format(T3D:string,sizeof(T3D:string),"%s:Line3D",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_Actor
		format(T3D:string,sizeof(T3D:string),"%s:Actor",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_ATM
		format(T3D:string,sizeof(T3D:string),"%s:ATM",T3D:string);
		modules_count++;
	#endif
	
	#if defined Tryg3D_Anims
		format(T3D:string,sizeof(T3D:string),"%s:Anims",T3D:string);
		modules_count++;
	#endif
	
	return T3D:string;
} 
 
Tryg3D::Function:: bool:Tryg3D::IsModuleLoaded(Tryg3DModule:moduleid){
	switch(moduleid){
		case TRYG3D_MODULEID_MAPANDREAS:	return Tryg3D_Module_MapAndreas;
		case TRYG3D_MODULEID_COLANDREAS:	return Tryg3D_Module_ColAndreas;
		case TRYG3D_MODULEID_YSF:			return Tryg3D_Module_YSF;
		case TRYG3D_MODULEID_STREAMER:		return Tryg3D_Module_Streamer;
		case TRYG3D_MODULEID_FOXFOREACH:	return Tryg3D_Module_FoxForeach;
		case TRYG3D_MODULEID_YSIFOREACH:	return Tryg3D_Module_YSIForeach;
		case TRYG3D_MODULEID_FCNPC:			return Tryg3D_Module_FCNPC;
		case TRYG3D_MODULEID_STREAM3D:		return Tryg3D_Module_Stream3D;
		case TRYG3D_MODULEID_LINE3D:		return Tryg3D_Module_Line3D;
		case TRYG3D_MODULEID_ACTOR:			return Tryg3D_Module_Actor;
		case TRYG3D_MODULEID_ATM:			return Tryg3D_Module_ATM;
		case TRYG3D_MODULEID_ANIMS:			return Tryg3D_Module_Anims;
	}
	return false;
}
 
 
Tryg3D::Function:: Tryg3D::GetEfficiency(bool:use_colandreas=false){
	new test_time = GetTickCount();
	#if defined Tryg3D_ColAndreas
		if(use_colandreas){
			for(new rx = 0; rx < 360; rx++){
				for(new rz = 0; rz < 360; rz++){
					new Float:tx,Float:ty,Float:tz,Float:grx,Float:grz,Float:dist;
					GetPointInFront3DCol(0.0,0.0,0.0,float(rx),float(rz),100.0,tx,ty,tz);
					GetRotationFor2Point3D(0.0,0.0,0.0,tx,ty,tz,grx,grz);
					dist = GetDistanceBetweenPoints3D(0.0,0.0,0.0,tx,ty,tz);
					GetPointFor2Point3DEx(0.0,0.0,0.0,tx,ty,tz,(dist/2.0),tx,ty,tz);
				}
			}
		} else {
			for(new rx = 0; rx < 360; rx++){
				for(new rz = 0; rz < 360; rz++){
					new Float:tx,Float:ty,Float:tz,Float:grx,Float:grz,Float:dist;
					GetPointInFront3D(0.0,0.0,0.0,float(rx),float(rz),100.0,tx,ty,tz);
					GetRotationFor2Point3D(0.0,0.0,0.0,tx,ty,tz,grx,grz);
					dist = GetDistanceBetweenPoints3D(0.0,0.0,0.0,tx,ty,tz);
					GetPointFor2Point3DEx(0.0,0.0,0.0,tx,ty,tz,(dist/2.0),tx,ty,tz);
				}
			}
		}
	#else
		#pragma unused use_colandreas
		for(new rx = 0; rx < 360; rx++){
			for(new rz = 0; rz < 360; rz++){
				new Float:tx,Float:ty,Float:tz,Float:grx,Float:grz,Float:dist;
				GetPointInFront3D(0.0,0.0,0.0,float(rx),float(rz),100.0,tx,ty,tz);
				GetRotationFor2Point3D(0.0,0.0,0.0,tx,ty,tz,grx,grz);
				dist = GetDistanceBetweenPoints3D(0.0,0.0,0.0,tx,ty,tz);
				GetPointFor2Point3DEx(0.0,0.0,0.0,tx,ty,tz,(dist/2.0),tx,ty,tz);
			}
		}
	#endif
	return (GetTickCount()-test_time);
} 
 
#if defined Tryg3D_ATM 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * ATM Module Functions                                                                                                             *
 * Code anti-collision: YES                                                                                                         *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#if !defined randomex
	#define randomex(%0,%1) 							(random((%1)-(%0)+1)+(%0))
#endif

#define Tryg3D_KeyPressed(%0) 							(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define Tryg3D_KeyReleased(%0)							(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#define Tryg3D_KeyHolding(%0) 							((newkeys & (%0)) == (%0))

//%d:%02d:%02d:%02d
#define Tryg3D_SecToTimeDay(%0)							((%0) / 86400),(((%0) % 86400) / 3600),((((%0) % 86400) % 3600) / 60),((((%0) % 86400) % 3600) % 60)
#define Tryg3D_MSToTimeDay(%0)							Tryg3D_SecToTimeDay((%0)/1000)
//%02d:%02d:%02d
#define Tryg3D_SecToTime(%0)							((%0) / 3600),(((%0) % 3600) / 60),(((%0) % 3600) % 60)
#define Tryg3D_MSToTime(%0)								Tryg3D_SecToTime((%0)/1000)
//%02d:%02d
#define Tryg3D_SecToTimeMini(%0)						((%0) / 60),((%0) % 60)
#define Tryg3D_MSToTimeMini(%0)							Tryg3D_SecToTimeMini((%0)/1000)

#define v3Dfunction%0(%1)								forward %0(%1); public %0(%1) 
 
Tryg3D::Function:: Tryg3D::GetSAMIncludeVersion(value,name[],maxdest = sizeof(name)){
	format(name,maxdest,"%d.%d.%d",(value / 10000),((value % 10000) / 100),((value % 10000) % 100));
}
 
 
Tryg3D::Function:: Tryg3D::DisableADMLogging(bool:disable){
	if(disable){
		SetSVarInt("ADM:Logging:Disable",1);
	} else {
		SetSVarInt("ADM:Logging:Disable",0);
	}
} 
 
#endif 
 
#if defined Tryg3D_Actor 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Actor Functions                                                                                                                  *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#define GetActorDistanceFromPoint(%0,%1,%2,%3)	GetElementDistanceFromPoint((%0),item_actor,(%1),(%2),(%3))
#define GetPlayerActorDistance(%1,%2)			GetElementsDistance((%1),item_player,(%1),item_actor)
#define IsActorInRangeOfPoint(%0,%1,%2,%3,%4)	(GetElementDistanceFromPoint((%0),item_actor,(%2),(%3),(%4)) <= (%1))	
 
 
Tryg3D::Function:: CountActors(){
	new T3D:count = 0;
	for(new i = 0, j = GetActorPoolSize(); i <= j; i++){
		if(IsValidActor(i)){
			T3D:count++;
		}
	}
	return T3D:count;
} 
 
Tryg3D::Function:: CountVisibleActors(playerid){
	new T3D:count = 0;
	for(new i = 0, j = GetActorPoolSize(); i <= j; i++){
		if(IsValidActor(i) && IsActorStreamedIn(i,playerid)){
			T3D:count++;
		}
	}
	return T3D:count;
} 
 
#endif 
 
#if defined Tryg3D_Stream3D 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Stream3D Functions                                                                                                               *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#define StreamCreate(%0)							Stream:%0[Stream3D]
#define GetStreamType(%0) 							(%0[T3D:type]) 
 
Tryg3D::Function:: bool:IsValidStream(Stream:StreamData[Stream3D]){
	return (StreamData[T3D:type] != s_invalid);
} 
 
Tryg3D::Function:: Stream:StreamCircle(Float:x,Float:y,Float:radius){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_circle;
	StreamData[T3D:X] = x;
	StreamData[T3D:Y] = y;
	StreamData[T3D:R] = radius;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamCylinder3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:radius){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_cylinder3d;
	StreamData[T3D:minX] = xA;
	StreamData[T3D:minY] = yA;
	StreamData[T3D:minZ] = zA;
	StreamData[T3D:maxX] = xB;
	StreamData[T3D:maxY] = yB;
	StreamData[T3D:maxZ] = zB;
	StreamData[T3D:R] = radius;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamCone3D(Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:pointA_radius,Float:pointB_radius){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_cone;
	StreamData[T3D:minX] = xA;
	StreamData[T3D:minY] = yA;
	StreamData[T3D:minZ] = zA;
	StreamData[T3D:maxX] = xB;
	StreamData[T3D:maxY] = yB;
	StreamData[T3D:maxZ] = zB;
	StreamData[T3D:X] = pointA_radius;
	StreamData[T3D:Y] = pointB_radius;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamCube3D(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:size_x,Float:size_y,Float:size_z){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_cube3d;
	StreamData[T3D:X] = x;
	StreamData[T3D:Y] = y;
	StreamData[T3D:Z] = z;
	StreamData[T3D:minX] = rx;
	StreamData[T3D:minY] = ry;
	StreamData[T3D:minZ] = rz;
	StreamData[T3D:maxX] = size_x;
	StreamData[T3D:maxY] = size_y;
	StreamData[T3D:maxZ] = size_z;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamCylinder2D(Float:x,Float:y,Float:minz,Float:maxz,Float:radius){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_cylinder2d;
	StreamData[T3D:X] = x;
	StreamData[T3D:Y] = y;
	StreamData[T3D:minZ] = minz;
	StreamData[T3D:maxZ] = maxz;
	StreamData[T3D:R] = radius;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamSphere(Float:x,Float:y,Float:z,Float:radius){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_sphere;
	StreamData[T3D:X] = x;
	StreamData[T3D:Y] = y;
	StreamData[T3D:Z] = z;
	StreamData[T3D:R] = radius;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamRectangle(Float:minx,Float:miny,Float:maxx,Float:maxy){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_rectangle;
	StreamData[T3D:minX] = minx;
	StreamData[T3D:minY] = miny;
	StreamData[T3D:maxX] = maxx;
	StreamData[T3D:maxY] = maxy;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamCube(Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_cube2d;
	StreamData[T3D:minX] = minx;
	StreamData[T3D:minY] = miny;
	StreamData[T3D:minZ] = minz;
	StreamData[T3D:maxX] = maxx;
	StreamData[T3D:maxY] = maxy;
	StreamData[T3D:maxZ] = maxz;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamCircularSector(Float:x,Float:y,Float:rz,Float:radius,Float:view_angle){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_circularsector;
	StreamData[T3D:X] = x;
	StreamData[T3D:Y] = y;
	StreamData[T3D:minZ] = rz;
	StreamData[T3D:R] = radius;
	StreamData[T3D:maxZ] = view_angle;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamSphericalSector(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,Float:vrx,Float:vrz){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_sphericalsector;
	StreamData[T3D:X] = x;
	StreamData[T3D:Y] = y;
	StreamData[T3D:Z] = z;
	StreamData[T3D:minX] = rx;
	StreamData[T3D:minZ] = rz;
	StreamData[T3D:R] = radius;
	StreamData[T3D:maxX] = vrx;
	StreamData[T3D:maxZ] = vrz;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamEllipse(Float:cx,Float:cy,Float:size_x,Float:size_y){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_ellipse;
	StreamData[T3D:X] = cx;
	StreamData[T3D:Y] = cy;
	StreamData[T3D:minX] = size_x;
	StreamData[T3D:minY] = size_y;
	return StreamData;
} 
 
Tryg3D::Function:: Stream:StreamEllipticalCylinder2D(Float:cx,Float:cy,Float:minz,Float:maxz,Float:size_x,Float:size_y){
	new StreamCreate(StreamData);
	StreamData[T3D:type] = s_ellipticalcyl2d;
	StreamData[T3D:X] = cx;
	StreamData[T3D:Y] = cy;
	StreamData[T3D:minZ] = minz;
	StreamData[T3D:maxZ] = maxz;
	StreamData[T3D:minX] = size_x;
	StreamData[T3D:minY] = size_y;
	return StreamData;
} 
 
Tryg3D::Function:: bool:IsPointInStream(Float:x,Float:y,Float:z,Stream:StreamData[Stream3D]){
	switch(StreamData[T3D:type]){
		case s_circle:			return IsPointInCircle(x,y,StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:R]);
		case s_cylinder3d:		return IsPointInCylinder3D(x,y,z,StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],StreamData[T3D:R]);
		case s_cylinder2d:		return IsPointInCylinder2D(x,y,z,StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:maxZ],StreamData[T3D:R]);
		case s_sphere:			return IsPointInSphere(x,y,z,StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:R]);
		case s_rectangle:		return IsPointInRectangle(x,y,StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:maxX],StreamData[T3D:maxY]);
		case s_cube2d:			return IsPointInCube(x,y,z,StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ]);
		case s_circularsector:	return IsPointInCircularSector(x,y,StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:R],StreamData[T3D:maxZ]);
		case s_sphericalsector:	return IsPointInSphericalSector(x,y,z,StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:minX],StreamData[T3D:minZ],StreamData[T3D:R],StreamData[T3D:maxX],StreamData[T3D:maxZ]);
		case s_cone:			return IsPointInCone3D(x,y,z,StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],StreamData[T3D:X],StreamData[T3D:Y]);
		case s_cube3d:			return IsPointInCube3D(x,y,z,StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ]);
		case s_ellipse:			return IsPointInEllipse(x,y,StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minX],StreamData[T3D:minY]);
		case s_ellipticalcyl2d: return IsPointInEllipticalCylinder2D(x,y,z,StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:maxZ],StreamData[T3D:minX],StreamData[T3D:minY]);
	}
	return false;
} 
 
Tryg3D::Function:: bool:GetRandomPointInStream(Stream:StreamData[Stream3D],&Float:x,&Float:y,&Float:z){
	switch(StreamData[T3D:type]){
		case s_circle: {
			GetRandomPointInCircle(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:R],x,y);
			z = FLOAT_INFINITY;
			return true;
		}
		case s_cylinder3d: {
			GetRandomPointInCylinder3D(StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],StreamData[T3D:R],x,y,z);
			return true;
		}
		case s_cylinder2d: {
			GetRandomPointInCylinder2D(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:maxZ],StreamData[T3D:R],x,y,z);
			return true;
		}
		case s_sphere: {
			GetRandomPointInSphere(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:R],x,y,z);
			return true;
		}
		case s_rectangle: {
			GetRandomPointInRectangle(StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:maxX],StreamData[T3D:maxY],x,y);
			z = FLOAT_INFINITY;
			return true;
		}
		case s_cube2d: {
			GetRandomPointInCube(StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],x,y,z);
			return true;
		}
		case s_circularsector: {
			GetRandomPointInCircularSector(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:R],StreamData[T3D:maxZ],x,y);
			z = FLOAT_INFINITY;
			return true;
		}
		case s_sphericalsector: {
			GetRandomPointInSphericalSector(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:minX],StreamData[T3D:minZ],StreamData[T3D:R],StreamData[T3D:maxX],StreamData[T3D:maxZ],x,y,z);
			return true;
		}
		case s_cone: {
			GetRandomPointInCone3D(StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],StreamData[T3D:X],StreamData[T3D:Y],x,y,z);
			return true;
		}
		case s_cube3d: {
			GetRandomPointInCube3D(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],x,y,z);
			return true;
		}
		case s_ellipse: {
			GetRandomPointInEllipse(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minX],StreamData[T3D:minY],x,y);
			z = FLOAT_INFINITY;
			return true;
		}
		case s_ellipticalcyl2d: {
			GetRandomPointInEllipticalCyl2D(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:maxZ],StreamData[T3D:minX],StreamData[T3D:minY],x,y,z);
			return true;
		}
	}
	return false;
} 
 
Tryg3D::Function:: bool:GetRandomPointOnStream(Stream:StreamData[Stream3D],&Float:x,&Float:y,&Float:z){
	switch(StreamData[T3D:type]){
		case s_circle: {
			GetRandomPointOnCircle(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:R],x,y);
			z = FLOAT_INFINITY;
			return true;
		}
		case s_cylinder3d: {
			GetRandomPointOnCylinder3D(StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],StreamData[T3D:R],x,y,z);
			return true;
		}
		case s_cylinder2d: {
			GetRandomPointOnCylinder2D(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:maxZ],StreamData[T3D:R],x,y,z);
			return true;
		}
		case s_sphere: {
			GetRandomPointOnSphere(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:R],x,y,z);
			return true;
		}
		case s_rectangle: {
			GetRandomPointOnRectangle(StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:maxX],StreamData[T3D:maxY],x,y);
			z = FLOAT_INFINITY;
			return true;
		}
		case s_cube2d: {
			GetRandomPointOnCube(StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],x,y,z);
			return true;
		}
		case s_circularsector: {
			GetRandomPointOnCircularSector(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:R],StreamData[T3D:maxZ],x,y);
			z = FLOAT_INFINITY;
			return true;
		}
		case s_sphericalsector: {
			GetRandomPointOnSphericalSector(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:minX],StreamData[T3D:minZ],StreamData[T3D:R],StreamData[T3D:maxX],StreamData[T3D:maxZ],x,y,z);
			return true;
		}
		case s_cone: {
			GetRandomPointOnCone3D(StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],StreamData[T3D:X],StreamData[T3D:Y],x,y,z);
			return true;
		}
		case s_cube3d: {
			GetRandomPointOnCube3D(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:Z],StreamData[T3D:minX],StreamData[T3D:minY],StreamData[T3D:minZ],StreamData[T3D:maxX],StreamData[T3D:maxY],StreamData[T3D:maxZ],x,y,z);
			return true;
		}
		case s_ellipse: {
			GetRandomPointOnEllipse(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minX],StreamData[T3D:minY],x,y);
			z = FLOAT_INFINITY;
			return true;
		}
		case s_ellipticalcyl2d: {
			GetRandomPointOnEllipticalCyl2D(StreamData[T3D:X],StreamData[T3D:Y],StreamData[T3D:minZ],StreamData[T3D:maxZ],StreamData[T3D:minX],StreamData[T3D:minY],x,y,z);
			return true;
		}
	}
	return false;
} 
 
Tryg3D::Function:: bool:IsElementInStream(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Stream:StreamData[Stream3D]){
	new Float:px,Float:py,Float:pz;
	GetElementPos(elementid,element_type,px,py,pz);
	return IsPointInStream(px,py,pz,StreamData);
} 
 
Tryg3D::Function:: bool:IsVehicleFullyInStream(vehicleid,Stream:StreamData[Stream3D]){
	new Float:size_x,Float:size_y,Float:size_z,
		Float:x,Float:y,Float:z,
		Float:minx,Float:miny,Float:minz,
		Float:maxx,Float:maxy,Float:maxz;
	GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_SIZE,size_x,size_y,size_z);
	size_x /= 2.0, size_y /= 2.0, size_z /= 2.0;

	GetVehiclePos(vehicleid,x,y,z);
	
	minx = x - size_x;
	miny = y - size_y;
	minz = z - size_z;
	
	maxx = x + size_x;
	maxy = y + size_y;
	maxz = z + size_z;
	
	if(!IsPointInStream(minx,miny,minz,StreamData)) return false;
	if(!IsPointInStream(minx,miny,maxz,StreamData)) return false;
	if(!IsPointInStream(minx,maxy,minz,StreamData)) return false;
	if(!IsPointInStream(minx,maxy,maxz,StreamData)) return false;
	if(!IsPointInStream(maxx,miny,minz,StreamData)) return false;
	if(!IsPointInStream(maxx,miny,maxz,StreamData)) return false;
	if(!IsPointInStream(maxx,maxy,minz,StreamData)) return false;
	if(!IsPointInStream(maxx,maxy,maxz,StreamData)) return false;
	return true;
} 
 
#if defined Tryg3D_Streamer 
 
Tryg3D::Function:: Stream:ConvertAreaToStream(STREAMER_TAG_AREA areaid){
	new StreamCreate(StreamData);
	if(!IsValidDynamicArea(STREAMER_TAG_AREA areaid)) return StreamData;
	switch(Streamer_GetIntData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_TYPE)){
		case STREAMER_AREA_TYPE_CIRCLE: {
			StreamData[T3D:type] = s_circle;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_X,StreamData[T3D:X]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_Y,StreamData[T3D:Y]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_SIZE,StreamData[T3D:R]);
		}
		case STREAMER_AREA_TYPE_CYLINDER: {
			StreamData[T3D:type] = s_cylinder2d;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_X,StreamData[T3D:X]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_Y,StreamData[T3D:Y]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_Z,StreamData[T3D:minZ]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_Z,StreamData[T3D:maxZ]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_SIZE,StreamData[T3D:R]);
		}
		case STREAMER_AREA_TYPE_SPHERE: {
			StreamData[T3D:type] = s_sphere;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_X,StreamData[T3D:X]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_Y,StreamData[T3D:Y]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_Z,StreamData[T3D:Z]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_SIZE,StreamData[T3D:R]);
		}
		case STREAMER_AREA_TYPE_RECTANGLE: {
			StreamData[T3D:type] = s_rectangle;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_X,StreamData[T3D:minX]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_Y,StreamData[T3D:minY]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_X,StreamData[T3D:maxX]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_Y,StreamData[T3D:maxY]);
		}
		case STREAMER_AREA_TYPE_CUBOID: {
			StreamData[T3D:type] = s_cube2d;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_X,StreamData[T3D:minX]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_Y,StreamData[T3D:minY]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_Z,StreamData[T3D:minZ]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_X,StreamData[T3D:maxX]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_Y,StreamData[T3D:maxY]);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_Z,StreamData[T3D:maxZ]);
		}
	}
	return StreamData;
} 
 
#endif 
 
#endif 
 
#if defined Tryg3D_Line3D 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Line3D Functions                                                                                                                 *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
 

	
#define INVALID_LINE3D_POINT_ID						(-1)

#define Line3DCreate(%0,%1)							Line3D:%0[(%1)][LinePoint3D]
#define GetLine3DValue(%0,%1,%2)					%0[%1][T3D:%2]
#define SetLine3DValue(%0,%1,%2,%3)					%0[%1][T3D:%2] = (%3) 
 
Tryg3D::Function:: bool:GetLine3DPointPos(Line3D:LineData[][LinePoint3D],pointid,&Float:x,&Float:y,&Float:z,max_points = sizeof(LineData)){
	if(pointid >= max_points || pointid < 0) return false;
	x = GetLine3DValue(LineData,pointid,X);
	y = GetLine3DValue(LineData,pointid,Y);
	z = GetLine3DValue(LineData,pointid,Z);
	return true;
} 
 
Tryg3D::Function:: bool:SetLine3DPointPos(Line3D:LineData[][LinePoint3D],pointid,Float:x,Float:y,Float:z,max_points = sizeof(LineData)){
	if(pointid >= max_points || pointid < 0) return false;
	SetLine3DValue(LineData,pointid,X,x);
	SetLine3DValue(LineData,pointid,Y,y);
	SetLine3DValue(LineData,pointid,Z,z);
	return true;
}
 
 
Tryg3D::Function:: bool:GetLine3DPointRot(Line3D:LineData[][LinePoint3D],pointid,&Float:rx,&Float:ry,&Float:rz,max_points = sizeof(LineData)){
	if(pointid >= max_points || pointid < 0) return false;
	rx = GetLine3DValue(LineData,pointid,rX);
	ry = GetLine3DValue(LineData,pointid,rY);
	rz = GetLine3DValue(LineData,pointid,rZ);
	return true;
} 
 
Tryg3D::Function:: bool:SetLine3DPointRot(Line3D:LineData[][LinePoint3D],pointid,Float:rx,Float:ry,Float:rz,max_points = sizeof(LineData)){
	if(pointid >= max_points || pointid < 0) return false;
	SetLine3DValue(LineData,pointid,rX,rx);
	SetLine3DValue(LineData,pointid,rY,ry);
	SetLine3DValue(LineData,pointid,rZ,rz);
	return true;
} 
 
Tryg3D::Function:: CountLine3DPoints(Line3D:LineData[][LinePoint3D],max_points = sizeof(LineData)){
	new T3D:count = 0;
	for(new i = 0; i < max_points; i++){
		if(GetLine3DValue(LineData,i,PointUsed)) T3D:count++;
	}
	return T3D:count;
} 
 
Tryg3D::Function:: AddPointToLine3D(Line3D:LineData[][LinePoint3D],Float:x,Float:y,Float:z,Float:rx=INVALID_ROTATION,Float:ry=INVALID_ROTATION,Float:rz=INVALID_ROTATION,max_points = sizeof(LineData)){
	new pointid = CountLine3DPoints(LineData,max_points);
	if(pointid >= max_points || pointid < 0) return INVALID_LINE3D_POINT_ID;
	SetLine3DValue(LineData,pointid,PointUsed,true);
	SetLine3DValue(LineData,pointid,X,x);
	SetLine3DValue(LineData,pointid,Y,y);
	SetLine3DValue(LineData,pointid,Z,z);
	SetLine3DValue(LineData,pointid,rX,rx);
	SetLine3DValue(LineData,pointid,rY,ry);
	SetLine3DValue(LineData,pointid,rZ,rz);
	return pointid;
} 
 
Tryg3D::Function:: bool:RemovePointFromLine3D(Line3D:LineData[][LinePoint3D],pointid,max_points = sizeof(LineData)){
	if(pointid >= max_points || pointid < 0) return false;
	if(!GetLine3DValue(LineData,pointid,PointUsed)) return false;
	new end_pointid = CountLine3DPoints(LineData,max_points)-1;
	if(pointid == end_pointid){
		SetLine3DValue(LineData,pointid,PointUsed,false);
		SetLine3DPointPos(LineData,pointid,0.0,0.0,0.0,max_points);
		SetLine3DPointRot(LineData,pointid,0.0,0.0,0.0,max_points);
	} else {
		new Float:x,Float:y,Float:z;
		for(new i = pointid; i < end_pointid; i++){
			GetLine3DPointPos(LineData,i+1,x,y,z,max_points);
			SetLine3DPointPos(LineData,i,x,y,z,max_points);
			GetLine3DPointRot(LineData,i+1,x,y,z,max_points);
			SetLine3DPointRot(LineData,i,x,y,z,max_points);
		}
		SetLine3DValue(LineData,end_pointid,PointUsed,false);
		SetLine3DPointPos(LineData,end_pointid,0.0,0.0,0.0,max_points);
		SetLine3DPointRot(LineData,end_pointid,0.0,0.0,0.0,max_points);
	}
	return true;
} 
 
#endif 
 
#if defined Tryg3D_Streamer 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Streamer Functions                                                                                                               *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

new bool:T3D:Tryg3DStreamerExam = false;

#define TRYG3D_GET_STREAMER_VERSION						(0xFFFFFFFF)

#define Tryg3D_GetStreamerVersion()						(Streamer_IncludeFileVersion)
#define Tryg3D_GetValidStreamerVersion()				(Tryg3D::StreamerVersion)
#define IsDynamicObjectInRangeOfPoint(%0,%1,%2,%3,%4) 	(GetElementDistanceFromPoint((%0),item_dynamic_object,(%2),(%3),(%4)) <= (%1))
#define IsDynamicActorInRangeOfPoint(%0,%1,%2,%3,%4)	(GetElementDistanceFromPoint((%0),item_dynamic_actor,(%2),(%3),(%4)) <= (%1))
 
 
Tryg3D::Function:: bool:Tryg3D::IsValidStreamer(value){
	return (Tryg3D::GetStreamerVersion() == value);
} 
 
Tryg3D::Function:: Tryg3D::GetStreamerVersionName(name[],value = TRYG3D_GET_STREAMER_VERSION,maxdest = sizeof(name)){
	if(value == TRYG3D_GET_STREAMER_VERSION) value = Tryg3D::GetStreamerVersion();
	new T3D:version[10];
	format(T3D:version,sizeof(T3D:version),"%03x",value);
	format(name,maxdest,"%d.%d.%d",(T3D:version[0]-48),(T3D:version[1]-48),(T3D:version[2]-48));
} 
 
Tryg3D::Function:: Tryg3D::CheckStreamerVersion(){
	if(!Tryg3D::IsValidStreamer(Tryg3D::GetValidStreamerVersion())){
		T3D:Tryg3DStreamerExam = false;
		new T3D:str1[32], T3D:str2[32];
		Tryg3D::GetStreamerVersionName(T3D:str1,Tryg3D::GetStreamerVersion());
		Tryg3D::GetStreamerVersionName(T3D:str2,Tryg3D::GetValidStreamerVersion());
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Your Streamer %s It is not compatible with this version 3DTryg, update your streamer to %s",T3D:str1,T3D:str2);
		}
		Update3DTrygErrorCount();
	} else {
		T3D:Tryg3DStreamerExam = true;
	}
} 
 
Tryg3D::Function:: SetPlayerAbsolutePosition(playerid,Float:x,Float:y,Float:z,Float:angle,worldid = -1,interiorid = -1,compensatedtime = -1,freezeplayer = 1){
	Streamer_UpdateEx(playerid,x,y,z,worldid,interiorid,-1,compensatedtime,freezeplayer);
	if(worldid != -1) SetPlayerVirtualWorld(playerid,worldid);
	if(interiorid != -1) SetPlayerInterior(playerid,interiorid);
	SetPlayerPos(playerid,x,y,z);
	SetPlayerFacingAngle(playerid,angle);
	SetCameraBehindPlayer(playerid);
} 
 
Tryg3D::Function:: SetPlayerAbsolutePositionVeh(playerid,Float:x,Float:y,Float:z,Float:angle,worldid = -1,interiorid = -1,compensatedtime = -1,freezeplayer = 1){
	new T3D:vehicleid = GetPlayerVehicleID(playerid), seatid;
	if(T3D:vehicleid == 0){
		SetPlayerAbsolutePosition(playerid,x,y,z,angle,worldid,interiorid,compensatedtime,freezeplayer);
	} else {
		SetPlayerAbsolutePosition(playerid,x,y,z,angle,worldid,interiorid,compensatedtime,freezeplayer);
		if(worldid != -1) SetVehicleVirtualWorld(T3D:vehicleid,worldid);
		if(interiorid != -1) LinkVehicleToInterior(T3D:vehicleid,interiorid);
		SetVehiclePos(T3D:vehicleid,x,y,z);
		SetVehicleZAngle(T3D:vehicleid,angle);
		PutPlayerInVehicle(playerid,T3D:vehicleid,0);
		if(worldid != -1 || interiorid != -1){
			Tryg3DForeach(i){
				if(GetPlayerVehicleID(i) == T3D:vehicleid && (seatid = GetPlayerVehicleSeat(i)) != 0){
					if(worldid != -1) SetPlayerVirtualWorld(i,worldid);
					if(interiorid != -1) SetPlayerInterior(i,interiorid);
					PutPlayerInVehicle(i,T3D:vehicleid,seatid);
				}
			}
		}
	}
} 
 
Tryg3D::Function:: bool:IsVehicleFullyInDynamicArea(vehicleid,areaid){
	new Float:size_x,Float:size_y,Float:size_z,
		Float:x,Float:y,Float:z,
		Float:minx,Float:miny,Float:minz,
		Float:maxx,Float:maxy,Float:maxz;
	GetVehicleModelInfo(GetVehicleModel(vehicleid),VEHICLE_MODEL_INFO_SIZE,size_x,size_y,size_z);
	size_x /= 2.0, size_y /= 2.0, size_z /= 2.0;

	GetVehiclePos(vehicleid,x,y,z);
	
	minx = x - size_x;
	miny = y - size_y;
	minz = z - size_z;
	
	maxx = x + size_x;
	maxy = y + size_y;
	maxz = z + size_z;
	
	if(!IsPointInDynamicArea(areaid,minx,miny,minz)) return false;
	if(!IsPointInDynamicArea(areaid,minx,miny,maxz)) return false;
	if(!IsPointInDynamicArea(areaid,minx,maxy,minz)) return false;
	if(!IsPointInDynamicArea(areaid,minx,maxy,maxz)) return false;
	if(!IsPointInDynamicArea(areaid,maxx,miny,minz)) return false;
	if(!IsPointInDynamicArea(areaid,maxx,miny,maxz)) return false;
	if(!IsPointInDynamicArea(areaid,maxx,maxy,minz)) return false;
	if(!IsPointInDynamicArea(areaid,maxx,maxy,maxz)) return false;
	return true;
} 
 
Tryg3D::Function:: bool:GetRandomPointInDynamicArea(STREAMER_TAG_AREA areaid,&Float:tx,&Float:ty,&Float:tz){
	switch(Streamer_GetIntData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_TYPE)){
		case STREAMER_AREA_TYPE_CIRCLE: {
			new Float:x,Float:y,Float:size;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_X,x);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_Y,y);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_SIZE,size);
			GetRandomPointInCircle(x,y,size,tx,ty);
			tz = FLOAT_INFINITY;
			return true;
		}
		case STREAMER_AREA_TYPE_CYLINDER: {
			new Float:x,Float:y,Float:size,Float:minz,Float:maxz;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_X,x);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_Y,y);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_Z,minz);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_Z,maxz);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_SIZE,size);
			GetRandomPointInCylinder2D(x,y,minz,maxz,size,tx,ty,tz);
			return true;
		}
		case STREAMER_AREA_TYPE_SPHERE: {
			new Float:x,Float:y,Float:z,Float:size;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_X,x);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_Y,y);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_Z,z);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_SIZE,size);
			GetRandomPointInSphere(x,y,z,size,tx,ty,tz);
			return true;
		}
		case STREAMER_AREA_TYPE_RECTANGLE: {
			new Float:minx,Float:miny,Float:maxx,Float:maxy;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_X,minx);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_Y,miny);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_X,maxx);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_Y,maxy);
			GetRandomPointInRectangle(minx,miny,maxx,maxy,tx,ty);
			tz = FLOAT_INFINITY;
			return true;
		}
		case STREAMER_AREA_TYPE_CUBOID: {
			new Float:minx,Float:miny,Float:minz,Float:maxx,Float:maxy,Float:maxz;
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_X,minx);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_Y,miny);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MIN_Z,minz);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_X,maxx);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_Y,maxy);
			Streamer_GetFloatData(STREAMER_TYPE_AREA,_:areaid,E_STREAMER_MAX_Z,maxz);
			GetRandomPointInCube(minx,miny,minz,maxx,maxy,maxz,tx,ty,tz);
			return true;
		}
	}
	return false;
} 
 
#if defined Tryg3D_FCNPC 
 
Tryg3D::Function:: SetNPCAbsolutePosition(npcid,Float:x,Float:y,Float:z,Float:angle,worldid = -1,interiorid = -1,compensatedtime = -1,freezeplayer = 1){
	Streamer_UpdateEx(npcid,x,y,z,worldid,interiorid,-1,compensatedtime,freezeplayer);
	if(worldid != -1) FCNPC_SetVirtualWorld(npcid,worldid);
	if(interiorid != -1) FCNPC_SetInterior(npcid,interiorid);
	FCNPC_SetPosition(npcid,x,y,z);
	FCNPC_SetAngle(npcid,angle);
} 
 
#endif 
 
#endif 
 
#if defined Tryg3D_ColAndreas 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * ColAndreas Functions                                                                                                             *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
 
#define GET_COLANDREAS_VERSION						(0xFFFFFFFF)

#define GetColAndreasVersion()						(COLANDREAS_VERSION)
#define GetValidColAndreasVersion()					(Tryg3D::ColAndreasVersion)
#define IsCollisionFlag(%0,%1)						((%0) & (%1))
#define IsPointInUnderwater(%1,%2,%3)				(IsPointInWater((%1),(%2),(%3)) && ((%3) < -1.0))
#define GetPlayerCollisionFlags(%0)					GetElementCollisionFlags((%0),item_player)
#define GetVehicleCollisionFlags(%0)				GetElementCollisionFlags((%0),item_vehicle)

#define GetPointInFrontOnGround(%0,%1,%2,%3,%4,%5,%6,%7,%8) GetPointInFront3DCol((%0),(%1),(%2),(%3),(%4),(%8),(%5),(%6),(%7))
 
 
Tryg3D::Function:: bool:IsValidColAndreas(value){
	return (GetColAndreasVersion() >= value);
} 
 
Tryg3D::Function:: GetColAndreasVersionName(name[],value = GET_COLANDREAS_VERSION,maxdest = sizeof(name)){
	if(value == GET_COLANDREAS_VERSION) value = GetColAndreasVersion();
	format(name,maxdest,"%d.%d.%d",(value / 10000),((value % 10000) / 100),((value % 10000) % 100));
} 
 
Tryg3D::Function:: CheckColAndreasVersion(){
	if(!IsValidColAndreas(GetValidColAndreasVersion())){
		new T3D:str1[32], T3D:str2[32];
		GetColAndreasVersionName(T3D:str1,GetColAndreasVersion());
		GetColAndreasVersionName(T3D:str2,GetValidColAndreasVersion());
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Error: Your ColAndreas %s It is not compatible with this version 3DTryg, update your ColAndreas to %s",T3D:str1,T3D:str2);
		}
		Update3DTrygErrorCount();
	}
} 
 
Tryg3D::Function:: MovePointCol(Float:StartX,Float:StartY,Float:StartZ,Float:EndX,Float:EndY,Float:EndZ,&Float:x,&Float:y,&Float:z){
	x = y = z = 0.0;
	CA_RayCastLine(StartX,StartY,StartZ,EndX,EndY,EndZ,x,y,z);
	if(x == 0.0) x = EndX;
	if(y == 0.0) y = EndY;
	if(z == 0.0) z = EndZ;
} 
 
Tryg3D::Function:: bool:MovePointColCutLine(Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,&Float:x,&Float:y,&Float:z,Float:cut_size=0.0){
	new Float:radius, Float:rx, Float:rz;
	x = y = z = 0.0;
	CA_RayCastLine(sX,sY,sZ,eX,eY,eZ,x,y,z);
	if(x == 0.0) x = eX;
	if(y == 0.0) y = eY;
	if(z == 0.0) z = eZ;
	if((radius = GetDistanceBetweenPoints3D(sX,sY,sZ,x,y,z)) <= 0.0) return false;
	CompRotationFloat(-(acos((z-sZ)/radius)-90.0),rx);
	CompRotationFloat((atan2(y-sY,x-sX)-90.0),rz);
	if(radius-cut_size > 0.0) radius -= cut_size;
	GetPointInFront3D(sX,sY,sZ,rx,rz,radius,x,y,z);
	return true;
} 
 
Tryg3D::Function:: bool:MovePointColCutLineEx(Float:sX,Float:sY,Float:sZ,Float:eX,Float:eY,Float:eZ,&Float:x,&Float:y,&Float:z,Float:cut_size=0.0){
	new Float:radius, Float:rx, Float:rz;
	x = y = z = 0.0;
	CA_RayCastLine(sX,sY,sZ,eX,eY,eZ,x,y,z);
	if(x == 0.0) x = eX;
	if(y == 0.0) y = eY;
	if(z == 0.0) z = eZ;
	if((radius = GetDistanceBetweenPoints3D(sX,sY,sZ,x,y,z)) <= 0.0) return false;
	CompRotationFloat(-(acos((z-sZ)/radius)-90.0),rx);
	CompRotationFloat((atan2(y-sY,x-sX)-90.0),rz);
	if((radius-cut_size > cut_size) && (radius-cut_size > 0.0)){
		radius -= cut_size;
	} else {
		radius = FLOAT_DEFECT;
	}
	GetPointInFront3D(sX,sY,sZ,rx,rz,radius,x,y,z);
	return true;
}
 
 
//GetPointInFront3D (ColAndreas)
Tryg3D::Function:: GetPointInFront3DCol(Float:x,Float:y,Float:z,Float:rx,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	tx = x - (radius * floatcos(rx,degrees) * floatsin(rz,degrees));
	ty = y + (radius * floatcos(rx,degrees) * floatcos(rz,degrees));
	tz = z + (radius * floatsin(rx,degrees));
	MovePointCol(x,y,z,tx,ty,tz,tx,ty,tz);
} 
 
Tryg3D::Function:: GetPointInFront3DColEx(Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz,Float:radius,&Float:tx,&Float:ty,&Float:tz){
	new Float:vx,Float:vy,Float:vz,Float:trx,Float:trz;
	Tryg3D::EulerRotate(rx,ry,rz,0.0,1.0,0.0,vx,vy,vz,T3D:euler_zyx);
	GetRotationFor2Point3D(0.0,0.0,0.0,vx,vy,vz,trx,trz);
	GetPointInFront3DCol(x,y,z,trx,trz,radius,tx,ty,tz); 
}
 
 
//GetPointInFrontOfPlayer (ColAndreas)
Tryg3D::Function:: Float:GetPointInFrontOfPlayerCol(playerid,&Float:tx,&Float:ty,Float:radius){
	new Float:rz,Float:z;
	GetPlayerPos(playerid,tx,ty,z);
	if(IsPlayerInAnyVehicle(playerid)){
		GetVehicleZAngle(GetPlayerVehicleID(playerid),rz);
	} else {
		GetPlayerFacingAngle(playerid,rz);
	}
	GetPointInFront3DCol(tx,ty,z,0.0,rz,radius,tx,ty,z);
	return rz;
} 
 
//GetPointInFrontOfCamera2D (ColAndreas)
Tryg3D::Function:: Float:GetPointInFrontOfCamera2DCol(playerid,&Float:tx,&Float:ty,Float:radius){
	new Float:x,Float:y,Float:z,Float:rz;
	GetPlayerCameraPos(playerid,x,y,z);
	GetPlayerCameraZAngle(playerid,rz);
	GetPointInFront3DCol(x,y,z,0.0,rz,radius,tx,ty,z);
	return rz;
} 
 
//GetPointInFrontOfCamera3D (ColAndreas)
Tryg3D::Function:: GetPointInFrontOfCamera3DCol(playerid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
	new Float:x,Float:y,Float:z;
	GetPlayerCameraPos(playerid,x,y,z);
	GetPlayerCameraRotation(playerid,rx,rz);
	GetPointInFront3DCol(x,y,z,rx,rz,radius,tx,ty,tz);
} 
 
//GetPointInFrontOfVehicle2D (ColAndreas)
Tryg3D::Function:: Float:GetPointInFrontOfVehicle2DCol(vehicleid,&Float:tx,&Float:ty,Float:radius){
	new Float:rx,Float:ry,Float:rz,Float:x,Float:y,Float:z;
	GetVehiclePos(vehicleid,x,y,z);
	Tryg3D::GetVehicleRotation(vehicleid,rx,ry,rz);
	GetPointInFront3DCol(x,y,z,0.0,rz,radius,tx,ty,z);
	return rz;
} 
 
//GetPointInFrontOfVehicle3D (ColAndreas)
Tryg3D::Function:: GetPointInFrontOfVehicle3DCol(vehicleid,&Float:tx,&Float:ty,&Float:tz,Float:radius,&Float:rx=0.0,&Float:rz=0.0){
	new Float:ry,Float:x,Float:y,Float:z;
	GetVehiclePos(vehicleid,x,y,z);
	Tryg3D::GetVehicleRotation(vehicleid,rx,ry,rz);
	GetPointInFront3DCol(x,y,z,rx,rz,radius,tx,ty,tz);
} 
 
Tryg3D::Function:: Float:UndergroundFindZ(Float:x,Float:y,&Float:z=0.0){
	z = 0.0;
	CA_RayCastLine(x,y,-0.002,x,y,-100.0,x,y,z);
	return z;
} 
 
Tryg3D::Function:: Float:InteriorFindZ(Float:px,Float:py,Float:pz=1000.0,Float:size=2.0,&Float:z=0.0){
	z = 0.0;
	CA_RayCastLine(px,py,pz+size,px,py,pz-100.0,px,py,z);
	return z;
} 
 
Tryg3D::Function:: bool:IsPointInWater(Float:x,Float:y,Float:z=0.0){
	if(z > 0.0) return false;
	new Float:tmpzA, Float:tmpzB;
	Tryg3D::MapAndreasFindZ(x,y,tmpzA);
	UndergroundFindZ(x,y,tmpzB);
	return ((z >= tmpzB) && (tmpzB < 0.0) && (tmpzA > -0.001 && tmpzA < 0.001));
} 
 
Tryg3D::Function:: bool:IsPointInUnderground(Float:x,Float:y,Float:z){
	new Float:tmpzA;
	Tryg3D::MapAndreasFindZ(x,y,tmpzA);
	return (z < tmpzA && !IsPointInWater(x,y,z));
} 
 
Tryg3D::Function:: bool:IsPointInAir(Float:x,Float:y,Float:z,bool:interior=false,Float:max_distance=2.2){
	new Float:tmpzA;
	if(interior){
		InteriorFindZ(x,y,z,2.0,tmpzA);
	} else {
		Tryg3D::MapAndreasFindZ(x,y,tmpzA);
	}
	return (z >= tmpzA+max_distance);
} 
 
Tryg3D::Function:: bool:IsPointInGround(Float:x,Float:y,Float:z,bool:interior=false,Float:max_distance=2.2){
	if(z <= 0.0) return false;
	new Float:tmpzA;
	if(interior){
		InteriorFindZ(x,y,z,2.0,tmpzA);
	} else {
		Tryg3D::MapAndreasFindZ(x,y,tmpzA);
	}
	return (z <= tmpzA+max_distance);
} 
 
Tryg3D::Function:: GetPointCollisionFlags(Float:x,Float:y,Float:z,interiorid=0){
	new bool:isinterior = false, flag_value;
	if(interiorid != 0){
		flag_value |= POSITION_FLAG_INTERIOR;
		isinterior = true;
	} else {
		flag_value |= POSITION_FLAG_WORLD;
	}
	
	if(IsPointInUnderwater(x,y,z)){
		flag_value |= POSITION_FLAG_WATER;
		flag_value |= POSITION_FLAG_UNDERWATER;
	} else if(IsPointInWater(x,y,z)){
		flag_value |= POSITION_FLAG_WATER;
	} else if(IsPointInAir(x,y,z,isinterior,2.2)){
		flag_value |= POSITION_FLAG_AIR;
	} else if(IsPointInUnderground(x,y,z)){
		flag_value |= POSITION_FLAG_UNDERGROUND;
	} else {
		flag_value |= POSITION_FLAG_GROUND;
	}
	return flag_value;
} 
 
Tryg3D::Function:: bool:IsBetweenPlayersIsWall(playerid,targetid){
	new Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:xC,Float:yC,Float:zC;
	GetPlayerPos(playerid,xA,yA,zA);
	GetPlayerPos(targetid,xB,yB,zB);
	CA_RayCastLine(xA,yA,zA,xB,yB,zB,xC,yC,zC);
	return !(xC == 0.0 || yC == 0.0 || zC == 0.0);
} 
 
Tryg3D::Function:: bool:IsBetweenPlayerToPointIsWall(playerid,Float:x,Float:y,Float:z){
	new Float:xA,Float:yA,Float:zA,Float:xC,Float:yC,Float:zC;
	GetPlayerPos(playerid,xA,yA,zA);
	CA_RayCastLine(xA,yA,zA,x,y,z,xC,yC,zC);
	return !(xC == 0.0 || yC == 0.0 || zC == 0.0);
} 
 
Tryg3D::Function:: bool:GetPointInWallForPoint(Float:x,Float:y,Float:z,Float:radius,&Float:tx,&Float:ty,&Float:tz,Float:sector=90.0){
	if(sector <= 0.0 || sector > 360.0) return false;
	new Float:px,Float:py,Float:pz,Float:tmp_dist,Float:near_dist = 20000.0,sec_cnt = floatround(360.0/sector);
	if(sec_cnt > 360) sec_cnt = 360;
	
	for(new i = 0; i < sec_cnt; i++){
		GetPointInFront3DCol(x,y,z,0.0,CompRotationFloat(sector*i),radius,px,py,pz); 
		tmp_dist = GetDistanceBetweenPoints3D(x,y,z,px,py,pz);
		if(tmp_dist < near_dist){
			near_dist = tmp_dist;
			tx = px;
			ty = py;
			tz = pz;
		}
	}
	return true;
} 
 
Tryg3D::Function:: bool:IsPlayerInRangeOfElement(playerid,Float:range,TRYG3D_ELEMENT_TAG targetid,Item3D_Type:target_type=item_player,bool:testLOS=true){
	new Float:x,Float:y,Float:z;
	if(!GetElementPos(targetid,target_type,x,y,z)) return false;
	if(testLOS){
		return (IsPlayerInRangeOfPoint(playerid,range,x,y,z) && !IsBetweenPlayerToPointIsWall(playerid,x,y,z));
	} else {
		return bool:IsPlayerInRangeOfPoint(playerid,range,x,y,z);
	}
} 
 
Tryg3D::Function:: bool:IsElementInRangeOfPoint(Float:x,Float:y,Float:z,Float:range,TRYG3D_ELEMENT_TAG targetid,Item3D_Type:target_type=item_player,bool:testLOS=true){
	new Float:tx,Float:ty,Float:tz;
	if(!GetElementPos(targetid,target_type,tx,ty,tz)) return false;
	if(testLOS){
		new Float:xC,Float:yC,Float:zC;
		CA_RayCastLine(x,y,z,tx,ty,tz,xC,yC,zC);
		return (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz) <= range && (xC == 0.0 && yC == 0.0 && zC == 0.0));
	} else {
		return (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz) <= range);
	}
} 
 
Tryg3D::Function:: bool:IsElementInRangeOfElement(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:range,TRYG3D_ELEMENT_TAG targetid,Item3D_Type:target_type=item_player,bool:testLOS=true){
	new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz;
	if(!GetElementPos(elementid,element_type,x,y,z)) return false;
	if(!GetElementPos(targetid,target_type,tx,ty,tz)) return false;
	if(testLOS){
		new Float:xC,Float:yC,Float:zC;
		CA_RayCastLine(x,y,z,tx,ty,tz,xC,yC,zC);
		return (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz) <= range && (xC == 0.0 && yC == 0.0 && zC == 0.0));
	} else {
		return (GetDistanceBetweenPoints3D(x,y,z,tx,ty,tz) <= range);
	}
} 
 
Tryg3D::Function:: bool:IsBetweenElementsIsWall(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,TRYG3D_ELEMENT_TAG targetid,Item3D_Type:target_type){
	new Float:xA,Float:yA,Float:zA,Float:xB,Float:yB,Float:zB,Float:xC,Float:yC,Float:zC;
	if(!GetElementPos(elementid,element_type,xA,yA,zA)) return false;
	if(!GetElementPos(targetid,target_type,xB,yB,zB)) return false;
	CA_RayCastLine(xA,yA,zA,xB,yB,zB,xC,yC,zC);
	return !(xC == 0.0 || yC == 0.0 || zC == 0.0);
} 
 
Tryg3D::Function:: bool:IsBetweenElementToPointIsWall(Float:x,Float:y,Float:z,TRYG3D_ELEMENT_TAG targetid,Item3D_Type:target_type){
	new Float:xB,Float:yB,Float:zB,Float:xC,Float:yC,Float:zC;
	if(!GetElementPos(targetid,target_type,xB,yB,zB)) return false;
	CA_RayCastLine(x,y,z,xB,yB,zB,xC,yC,zC);
	return !(xC == 0.0 || yC == 0.0 || zC == 0.0);
}
 
 
Tryg3D::Function:: GetElementCollisionFlags(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type){
	new Float:x,Float:y,Float:z;
	if(!GetElementPos(elementid,element_type,x,y,z)) return 0;
	return GetPointCollisionFlags(x,y,z);
}
 
 
Tryg3D::Function:: bool:GetElementOrientationPosCol(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,element_orientation:orientation,Float:distance,&Float:tx,&Float:ty,&Float:tz){
	new Float:x,Float:y,Float:z,Float:rx,Float:ry,Float:rz;
	if(!GetElementPos(elementid,element_type,x,y,z)) return false;
	switch(element_type){
		case item_player: {
			GetPlayerFacingAngle(_:elementid,rz);
		}
		case item_npc: {
			#if defined Tryg3D_FCNPC
				if(FCNPC_IsValid(_:elementid)){
					rz = FCNPC_GetAngle(_:elementid);
				} else {
					GetPlayerFacingAngle(_:elementid,rz);
				}
			#else
				GetPlayerFacingAngle(_:elementid,rz);
			#endif
		}
		#if defined Tryg3D_Actor
			case item_actor: {
				GetActorFacingAngle(_:elementid,rz);
			}
		#endif
		case item_object: {
			GetObjectRot(_:elementid,rx,ry,rz);
		}
		case item_vehicle: {
			Tryg3D::GetVehicleRotation(_:elementid,rx,ry,rz);
		}
		#if defined Tryg3D_Streamer
			case item_dynamic_object: {
				GetDynamicObjectRot(STREAMER_TAG_OBJECT (_:elementid),rx,ry,rz);
			}
			case item_dynamic_actor: {
				GetDynamicActorFacingAngle(STREAMER_TAG_ACTOR (_:elementid),rz);
			}
		#endif
		default: return false;
	}
	
	switch(element_type){
		case item_player, item_npc, item_actor, item_dynamic_actor: {
			switch(orientation){
				case o_left:	GetPointInFront3DCol(x,y,z,0.0,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				case o_right:	GetPointInFront3DCol(x,y,z,0.0,CompRotationFloat(rz-90.0),distance,tx,ty,tz);
				case o_up:		GetPointInFront3DCol(x,y,z,90.0,0.0,distance,tx,ty,tz);
				case o_down:	GetPointInFront3DCol(x,y,z,270.0,0.0,distance,tx,ty,tz);
				case o_front:	GetPointInFront3DCol(x,y,z,0.0,rz,distance,tx,ty,tz);
				case o_back:	GetPointInFront3DCol(x,y,z,0.0,CompRotationFloat(rz+180.0),distance,tx,ty,tz);
			}
		}
		case item_vehicle, item_object, item_dynamic_object: {
			switch(orientation){
				case o_left:	GetPointInFront3DCol(x,y,z,ry,CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				case o_right:	GetPointInFront3DCol(x,y,z,CompRotationFloat(ry+180.0),CompRotationFloat(rz+90.0),distance,tx,ty,tz);
				case o_up:		{
					GetElementUpPos(elementid,element_type,distance,tx,ty,tz);
					MovePointCol(x,y,z,tx,ty,tz,tx,ty,tz);
				}
				case o_down:	{
					GetElementUpPos(elementid,element_type,distance,tx,ty,tz,true);
					MovePointCol(x,y,z,tx,ty,tz,tx,ty,tz);
				}
				case o_front:	GetPointInFront3DCol(x,y,z,rx,rz,distance,tx,ty,tz);
				case o_back:	GetPointInFront3DCol(x,y,z,CompRotationFloat(rx+180.0),rz,distance,tx,ty,tz);
			}
		}
	}
	return true;
} 
 
Tryg3D::Function:: bool:GetWallRotation(Float:sx,Float:sy,Float:sz,Float:ex,Float:ey,Float:ez,&Float:rx,&Float:rz,&Float:px=0.0,&Float:py=0.0,&Float:pz=0.0,Float:size=1.0,Float:cut_size=0.0){
	new Float:line_rx, Float:line_rz, Float:tmp_float;
	if(!GetRotationFor2Point3D(sx,sy,sz,ex,ey,ez,line_rx,line_rz)) return false;
	
	new VecStart[4][Vectors3D], VecEnd[4][Vectors3D], VecProduct[4][Vectors3D];
	
	//Start: Right -> Left
	GetPointInFront3D(sx,sy,sz,line_rx,CompRotationFloat(line_rz-90.0),size,VecStart[0][T3D:X],VecStart[0][T3D:Y],VecStart[0][T3D:Z]);
	GetPointInFront3D(sx,sy,sz,line_rx,CompRotationFloat(line_rz+90.0),size,VecStart[1][T3D:X],VecStart[1][T3D:Y],VecStart[1][T3D:Z]);
	
	//Start: Down -> Up
	GetPointInFront3D(sx,sy,sz,CompRotationFloat(line_rx-90.0),line_rz,size,VecStart[2][T3D:X],VecStart[2][T3D:Y],VecStart[2][T3D:Z]);
	GetPointInFront3D(sx,sy,sz,CompRotationFloat(line_rx+90.0),line_rz,size,VecStart[3][T3D:X],VecStart[3][T3D:Y],VecStart[3][T3D:Z]);
	
	//End: Right -> Left
	GetPointInFront3D(ex,ey,ez,line_rx,CompRotationFloat(line_rz-90.0),size,VecEnd[0][T3D:X],VecEnd[0][T3D:Y],VecEnd[0][T3D:Z]);
	GetPointInFront3D(ex,ey,ez,line_rx,CompRotationFloat(line_rz+90.0),size,VecEnd[1][T3D:X],VecEnd[1][T3D:Y],VecEnd[1][T3D:Z]);
	
	//End: Down -> Up
	GetPointInFront3D(ex,ey,ez,CompRotationFloat(line_rx-90.0),line_rz,size,VecEnd[2][T3D:X],VecEnd[2][T3D:Y],VecEnd[2][T3D:Z]);
	GetPointInFront3D(ex,ey,ez,CompRotationFloat(line_rx+90.0),line_rz,size,VecEnd[3][T3D:X],VecEnd[3][T3D:Y],VecEnd[3][T3D:Z]);

	for(new i = 0; i < 4; i++){
		GetPointFor2Point3DEx(VecStart[1][T3D:X],VecStart[1][T3D:Y],VecStart[1][T3D:Z],VecEnd[i][T3D:X],VecEnd[i][T3D:Y],VecEnd[i][T3D:Z],20000.0,VecEnd[i][T3D:X],VecEnd[i][T3D:Y],VecEnd[i][T3D:Z]);
		MovePointCol(VecStart[i][T3D:X],VecStart[i][T3D:Y],VecStart[i][T3D:Z],VecEnd[i][T3D:X],VecEnd[i][T3D:Y],VecEnd[i][T3D:Z],VecProduct[i][T3D:X],VecProduct[i][T3D:Y],VecProduct[i][T3D:Z]);
	}
	
	MovePointColCutLine(sx,sy,sz,ex,ey,ez,px,py,pz,cut_size);
	
	if(!GetRotationFor2Point3D(VecProduct[0][T3D:X],VecProduct[0][T3D:Y],VecProduct[0][T3D:Z],VecProduct[1][T3D:X],VecProduct[1][T3D:Y],VecProduct[1][T3D:Z],tmp_float,rz)) return false;
	if(!GetRotationFor2Point3D(VecProduct[2][T3D:X],VecProduct[2][T3D:Y],VecProduct[2][T3D:Z],VecProduct[3][T3D:X],VecProduct[3][T3D:Y],VecProduct[3][T3D:Z],rx,tmp_float)) return false;
	return true;
}
 
 
#endif 
 
#if ((defined Tryg3D_MapAndreas) && (!defined Tryg3D_ColAndreas)) 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * MapAndreas Functions                                                                                                             *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
 
 
Tryg3D::Function:: GetPointInFrontOnGround(Float:x,Float:y,Float:z,Float:rx,Float:rz,&Float:tx,&Float:ty,&Float:tz,Float:max_distance){
	new Float:tmpz;
	Tryg3D::MapAndreasFindZ(x,y,tmpz);
	new Float:radius = GetDistanceBetweenPoints3D(x,y,z,x,y,tmpz),
		Float:cos = floatcos(rx+90.0,degrees),
		Float:dist;
	if(cos == 0.0){
		dist = radius;
	} else {
		dist = floatabs(radius/cos);
	}
	if((dist > max_distance) || (rx >= 0.0 && rx <= 180.0)){
		dist = max_distance;
	}
	GetPointInFront3D(x,y,z,rx,rz,dist,tx,ty,tz);
	if(!((dist > max_distance) || (rx >= 0.0 && rx <= 180.0))){
		Tryg3D::MapAndreasFindZ(tx,ty,tz);
	}
} 
 
Tryg3D::Function:: bool:IsPointInWater(Float:x,Float:y,Float:z=0.0){
	if(z > 0.0) return false;
	new Float:tmpz;
	Tryg3D::MapAndreasFindZ(x,y,tmpz);
	return (tmpz == 0.0);
} 
 
#endif 
 
#if (defined Tryg3D_MapAndreas || defined Tryg3D_ColAndreas) 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * MapAndreas/ColAndreas Functions                                                                                                  *
 *                                                                                                                                  *
 ************************************************************************************************************************************/ 
 
Tryg3D::Function:: GetGroundRotation(Float:x,Float:y,Float:size,&Float:rx,&Float:ry){
	new Float:tpx1,Float:tpy1,Float:tpz1,
		Float:tpx2,Float:tpy2,Float:tpz2,
		Float:tmp_float;
	GetPointInFront2D(x,y,0.0,size,tpx1,tpy1);
	GetPointInFront2D(x,y,180.0,size,tpx2,tpy2);
	Tryg3D::MapAndreasFindZ(tpx1,tpy1,tpz1);
	Tryg3D::MapAndreasFindZ(tpx2,tpy2,tpz2);
	GetRotationFor2Point3D(tpx1,tpy1,tpz1,tpx2,tpy2,tpz2,rx,tmp_float);
	
	GetPointInFront2D(x,y,90.0,size,tpx1,tpy1);
	GetPointInFront2D(x,y,270.0,size,tpx2,tpy2);
	Tryg3D::MapAndreasFindZ(tpx1,tpy1,tpz1);
	Tryg3D::MapAndreasFindZ(tpx2,tpy2,tpz2);
	GetRotationFor2Point3D(tpx1,tpy1,tpz1,tpx2,tpy2,tpz2,ry,tmp_float);
} 
 
Tryg3D::Function:: bool:IsPointInWaterOrientOfElement(TRYG3D_ELEMENT_TAG elementid,Item3D_Type:element_type,Float:radius,element_orientation:orientation=o_front){
	new Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z;
	if(!GetElementPos(elementid,element_type,px,py,pz)) return false;
	if(!GetElementOrientationPos(elementid,element_type,orientation,radius,x,y,z)) return false;
	return IsPointInWater(x,y,0.0);
} 
 
Tryg3D::Deprecated:: bool:IsPointInWaterFrontOfPlayer(playerid,Float:radius){
	new Float:x, Float:y, Float:z;
	GetPlayerPos(playerid,x,y,z);
	GetPointInFrontOfPlayer(playerid,x,y,radius);
	return IsPointInWater(x,y,0.0);
} 
 
#endif 
 
#if defined Tryg3D_YSF 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * YSF Functions                                                                                                                    *
 *                                                                                                                                  *
 ************************************************************************************************************************************/


#define GetPlayerHydraReactorRX(%0) 				CompRotationFloat((GetPlayerHydraReactorAngle(%0)/55.5555555))
#define IsPlayerHydraReactorBoost(%0)				(GetPlayerHydraReactorAngle(%0) == 0) 
 
Tryg3D::Function:: CountTextDraw(){
	new T3D:count = 0;
	for(new i = 0; i < MAX_TEXT_DRAWS; i++){
		if(IsValidTextDraw(Text:i)) T3D:count++;
	}
	return T3D:count;
} 
 
Tryg3D::Function:: CountVisibleTextDraw(playerid){
	new T3D:count = 0;
	for(new i = 0; i < MAX_TEXT_DRAWS; i++){
		if(IsValidTextDraw(Text:i) && IsTextDrawVisibleForPlayer(playerid,Text:i)) T3D:count++;
	}
	return T3D:count;
} 
 
Tryg3D::Function:: CountPlayerTextDraw(playerid){
	new T3D:count = 0;
	for(new i = 0; i < MAX_PLAYER_TEXT_DRAWS; i++){
		if(IsValidPlayerTextDraw(playerid,PlayerText:i)) T3D:count++;
	}
	return T3D:count;
}
 
 
Tryg3D::Function:: CountVisiblePlayerTextDraw(playerid){
	new T3D:count = 0;
	for(new i = 0; i < MAX_PLAYER_TEXT_DRAWS; i++){
		if(IsValidPlayerTextDraw(playerid,PlayerText:i) && IsPlayerTextDrawVisible(playerid,PlayerText:i)) T3D:count++;
	}
	return T3D:count;
} 
 
Tryg3D::Function:: CountGangZone(){
	new T3D:count = 0;
	for(new i = 0; i < MAX_GANG_ZONES; i++){
		if(IsValidGangZone(i)) T3D:count++;
	}
	return T3D:count;
} 
 
Tryg3D::Function:: CountVisibleGangZone(playerid){
	new T3D:count = 0;
	for(new i = 0; i < MAX_GANG_ZONES; i++){
		if(IsValidGangZone(i) && IsGangZoneVisibleForPlayer(playerid,i)) T3D:count++;
	}
	return T3D:count;
}
 
 
Tryg3D::Function:: CountPlayerGangZone(playerid){
	new T3D:count = 0;
	for(new i = 0; i < MAX_GANG_ZONES; i++){
		if(IsValidPlayerGangZone(playerid,i)) T3D:count++;
	}
	return T3D:count;
} 
 
Tryg3D::Function:: CountVisiblePlayerGangZone(playerid){
	new T3D:count = 0;
	for(new i = 0; i < MAX_GANG_ZONES; i++){
		if(IsValidPlayerGangZone(playerid,i) && IsPlayerGangZoneVisible(playerid,i)) T3D:count++;
	}
	return T3D:count;
} 
 
Tryg3D::Function:: bool:IsVehicleOnSpawn(vehicleid,Float:check_radius=1.0){
	new Float:x,Float:y,Float:z,Float:rz,color1,color2;
	GetVehicleSpawnInfo(vehicleid,x,y,z,rz,color1,color2);
	return IsVehicleInRangeOfPoint(vehicleid,check_radius,x,y,z);
} 
 
Tryg3D::Function:: bool:IsPlayerOnSpawn(playerid,Float:check_radius=1.0){
	new teamid,modelid,Float:spawn_x,Float:spawn_y,Float:spawn_z,Float:z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo;
	GetSpawnInfo(playerid,teamid,modelid,spawn_x,spawn_y,spawn_z,z_angle,weapon1,weapon1_ammo,weapon2,weapon2_ammo,weapon3,weapon3_ammo);
	return bool:IsPlayerInRangeOfPoint(playerid,check_radius,spawn_x,spawn_y,spawn_z);
}
 
 
Tryg3D::Function:: GetPlayerRotation(playerid,&Float:rx,&Float:ry,&Float:rz){
	new Float:qw,Float:qx,Float:qy,Float:qz;
	GetPlayerRotationQuat(playerid,qw,qx,qy,qz);
	Tryg3D::QuatToEuler(rx,ry,rz,qw,qx,qy,qz);
} 
 
Tryg3D::Function:: GetRandomPointInGangZone(zoneid,&Float:tx,&Float:ty){
	new Float:minx,Float:miny,Float:maxx,Float:maxy;
	GangZoneGetPos(zoneid,minx,miny,maxx,maxy);
	GetRandomPointInRectangle(minx,miny,maxx,maxy,tx,ty);
}
 
 
Tryg3D::Function:: GetRandomPointInPlayerGangZone(playerid,zoneid,&Float:tx,&Float:ty){
	new Float:minx,Float:miny,Float:maxx,Float:maxy;
	PlayerGangZoneGetPos(playerid,zoneid,minx,miny,maxx,maxy);
	GetRandomPointInRectangle(minx,miny,maxx,maxy,tx,ty);
} 
 
#if defined ENABLE_3D_TRYG_TIMELINE_SYNC 
 
//YSF Timeline Sync (Beta Version)
new T3D:PlayerFirstSpawn[MAX_PLAYERS];

#define GetPlayerTimeline(%0)					GetPVarInt((%0),"T3D:PlayerTimeline")
#define IsPlayerVisibleOnServer(%0)				GetPVarInt((%0),"T3D:PlayerVisible") 
 
Tryg3D::Function:: UpdatePlayerTimeline(playerid){
	new tline = GetPlayerTimeline(playerid), pskin = GetPlayerSkin(playerid), pcolor = GetPlayerColor(playerid),
		Float:px, Float:py, Float:pz;
	GetPlayerPos(playerid,px,py,pz);
	Tryg3DForeach(i){
		if(i != playerid){
			if(tline == GetPlayerTimeline(i)){
				if(GetPlayerDistanceFromPoint(i,px,py,pz) <= Tryg3D::StreamDistance){
					ShowPlayerForPlayer(i,playerid);
					ShowPlayerForPlayer(playerid,i);
					
					SetPlayerSkinForPlayer(i,playerid,pskin);
					SetPlayerSkinForPlayer(playerid,i,GetPlayerSkin(i));
					
					if(Tryg3D::IsPlayerSpawned(playerid)){
						SetPlayerMarkerForPlayer(i,playerid,pcolor);
					}
					SetPlayerMarkerForPlayer(playerid,i,GetPlayerColor(i));
				}
			} else if(tline == -1){
				if(GetPlayerDistanceFromPoint(i,px,py,pz) <= Tryg3D::StreamDistance){
					ShowPlayerForPlayer(playerid,i);
					
					SetPlayerSkinForPlayer(playerid,i,GetPlayerSkin(i));
					
					SetPlayerMarkerForPlayer(playerid,i,GetPlayerColor(i));
				}
			} else {
				HidePlayerForPlayer(i,playerid);
				HidePlayerForPlayer(playerid,i);
				
				SetPlayerMarkerForPlayer(i,playerid,(pcolor & 0xFFFFFF00));
				SetPlayerMarkerForPlayer(playerid,i,(GetPlayerColor(i) & 0xFFFFFF00));
			}
		}
	}
} 
 
Tryg3D::Function:: SetPlayerTimeline(playerid,timeline){
	SetPVarInt(playerid,"T3D:PlayerTimeline",timeline);
	UpdatePlayerTimeline(playerid);
} 
 
Tryg3D::Function:: GetPlayerPos4D(playerid,&Float:x,&Float:y,&Float:z,&timeline){
	GetPlayerPos(playerid,x,y,z);
	timeline = GetPlayerTimeline(playerid);
} 
 
Tryg3D::Function:: SetPlayerPos4D(playerid,Float:x,Float:y,Float:z,timeline=0){
	SetPlayerPos(playerid,x,y,z);
	if(GetPlayerTimeline(playerid) != timeline) SetPlayerTimeline(playerid,timeline);
} 
 
Tryg3D::Function:: CreateDynamicExplosion4D(Float:x,Float:y,Float:z,type,Float:radius,worldid = -1,interiorid = -1,timeline = -1,playerid = -1,Float:distance = 200.0){
	if(playerid == -1){
		Tryg3DForeach(i){
			new Float:px, Float:py, Float:pz;
			if(IsPlayerInAnyVehicle(i)){
				GetVehiclePos(GetPlayerVehicleID(i),px,py,pz);
			} else {
				GetPlayerPos(i,px,py,pz);
			}
			if(GetPlayerTimeline(i) == timeline || timeline == -1){
				if((GetPlayerInterior(i) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(i) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
					CreateExplosionForPlayer(i,x,y,z,type,radius);
				}
			}
		}
	} else {
		if(IsPlayerConnected(playerid)){
			new Float:px, Float:py, Float:pz;
			if(IsPlayerInAnyVehicle(playerid)){
				GetVehiclePos(GetPlayerVehicleID(playerid),px,py,pz);
			} else {
				GetPlayerPos(playerid,px,py,pz);
			}
			if((GetPlayerInterior(playerid) == interiorid || interiorid == -1) && (GetPlayerVirtualWorld(playerid) == worldid || worldid == -1) && (VectorSize(px-x,py-y,pz-z) <= distance)){
				CreateExplosionForPlayer(playerid,x,y,z,type,radius);
			}
		}
	}
} 
 
Tryg3D::Function:: UpdatePlayerOnServer(playerid){
	Tryg3DForeach(i){
		if(playerid != i){
			if(IsPlayerVisibleOnServer(playerid)){
				RemovePlayerForPlayer(i,playerid);
				AddPlayerForPlayer(i,playerid,0);
			} else {
				RemovePlayerForPlayer(i,playerid);
			}
		}
	}
} 
 
Tryg3D::Function:: CheckPlayersOnServer(playerid){
	Tryg3DForeach(i){
		if(playerid != i){
			if(!IsPlayerVisibleOnServer(i)){
				RemovePlayerForPlayer(playerid,i);
			}
		}
	}
} 
 
Tryg3D::Function:: TogglePlayerVisibleOnServer(playerid,bool:toggle){
	TogglePlayerInServerQuery(playerid,toggle);
	SetPVarInt(playerid,"T3D:PlayerVisible",toggle?1:0);
	UpdatePlayerOnServer(playerid);
	if(toggle){
		SetPlayerTimeline(playerid,0);
	} else {
		SetPlayerTimeline(playerid,-1);
	}
} 
 
//Hook: OnPlayerStreamIn
public OnPlayerStreamIn(playerid,forplayerid){
	if(GetPlayerTimeline(playerid) == GetPlayerTimeline(forplayerid)){
		ShowPlayerForPlayer(forplayerid,playerid);
		ShowPlayerForPlayer(playerid,forplayerid);
		
		SetPlayerSkinForPlayer(forplayerid,playerid,GetPlayerSkin(playerid));
		SetPlayerSkinForPlayer(playerid,forplayerid,GetPlayerSkin(forplayerid));
		
		if(Tryg3D::IsPlayerSpawned(playerid)){
			SetPlayerMarkerForPlayer(forplayerid,playerid,GetPlayerColor(playerid));
		}
		SetPlayerMarkerForPlayer(playerid,forplayerid,GetPlayerColor(forplayerid));
	} else {
		HidePlayerForPlayer(forplayerid,playerid);
		HidePlayerForPlayer(playerid,forplayerid);
		
		SetPlayerMarkerForPlayer(forplayerid,playerid,(GetPlayerColor(playerid) & 0xFFFFFF00));
		SetPlayerMarkerForPlayer(playerid,forplayerid,(GetPlayerColor(forplayerid) & 0xFFFFFF00));
	}
	#if defined Tryg3D_OnPlayerStreamIn
		Tryg3D_OnPlayerStreamIn(playerid,forplayerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerStreamIn
	#undef OnPlayerStreamIn
#else
	#define _ALS_OnPlayerStreamIn
#endif
#define OnPlayerStreamIn Tryg3D_OnPlayerStreamIn
#if defined Tryg3D_OnPlayerStreamIn
	forward Tryg3D_OnPlayerStreamIn(playerid,forplayerid);
#endif

//Hook: OnPlayerConnect
public OnPlayerConnect(playerid){
	T3D:PlayerFirstSpawn[playerid] = true;
	SetPVarInt(playerid,"T3D:PlayerTimeline",0);
	SetPVarInt(playerid,"T3D:PlayerVisible",1);
	#if defined Tryg3D_OnPlayerConnect
		Tryg3D_OnPlayerConnect(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerConnect
	#undef OnPlayerConnect
#else
	#define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect Tryg3D_OnPlayerConnect
#if defined Tryg3D_OnPlayerConnect
	forward Tryg3D_OnPlayerConnect(playerid);
#endif

//Hook: OnPlayerSpawn
public OnPlayerSpawn(playerid){
	if(T3D:PlayerFirstSpawn[playerid]){
		T3D:PlayerFirstSpawn[playerid] = false;
		CheckPlayersOnServer(playerid);
	}
	UpdatePlayerTimeline(playerid);
	#if defined Tryg3D_OnPlayerSpawn
		Tryg3D_OnPlayerSpawn(playerid);
	#endif
	return 1;
}

#if defined _ALS_OnPlayerSpawn
	#undef OnPlayerSpawn
#else
	#define _ALS_OnPlayerSpawn
#endif
#define OnPlayerSpawn Tryg3D_OnPlayerSpawn
#if defined Tryg3D_OnPlayerSpawn
	forward Tryg3D_OnPlayerSpawn(playerid);
#endif 
 
#endif 
 
#endif 
 
#if defined Tryg3D_FCNPC 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * FCNPC Functions                                                                                                                  *
 *                                                                                                                                  *
 ************************************************************************************************************************************/
 
#define IsNPCInRangeOfPoint(%0,%1,%2,%3,%4)		(GetElementDistanceFromPoint((%0),item_npc,(%2),(%3),(%4)) <= (%1)) 
 
Tryg3D::Function:: Float:GetNPCSpeed(npcid){
	new Float:x,Float:y,Float:z;
	FCNPC_GetVelocity(npcid,x,y,z);
	return VectorSize(x,y,z);
} 
 
Tryg3D::Function:: Float:GetPointInFrontOfNPC(npcid,&Float:tx,&Float:ty,Float:radius){
	new Float:rz;
	FCNPC_GetPosition(npcid,tx,ty,rz);
	if(IsPlayerInAnyVehicle(npcid)){
		GetVehicleZAngle(FCNPC_GetVehicleID(npcid),rz);
	} else {
		rz = FCNPC_GetAngle(npcid);
	}
	GetPointInFront2D(tx,ty,rz,radius,tx,ty);
	return rz;
} 
 
Tryg3D::Function:: Float:GetNPCTargetAngle(npcid,Float:x,Float:y,&Float:rz=0.0){
	new Float:mx,Float:my;
	FCNPC_GetPosition(npcid,mx,my,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	return rz;
} 
 
Tryg3D::Function:: Float:SetNPCTargetAngle(npcid,Float:x,Float:y,&Float:rz=0.0){
	new Float:mx,Float:my;
	FCNPC_GetPosition(npcid,mx,my,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	FCNPC_SetAngle(npcid,rz);
	return rz;
} 
 
Tryg3D::Function:: Float:GetNPCTargetNPCAngle(npcid,targetid,&Float:rz=0.0){
	new Float:mx,Float:my,Float:x,Float:y;
	FCNPC_GetPosition(npcid,mx,my,rz);
	FCNPC_GetPosition(targetid,x,y,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	return rz;
} 
 
Tryg3D::Function:: Float:SetNPCTargetNPCAngle(npcid,targetid,&Float:rz=0.0){
	new Float:mx,Float:my,Float:x,Float:y;
	FCNPC_GetPosition(npcid,mx,my,rz);
	FCNPC_GetPosition(targetid,x,y,rz);
	GetRotationFor2Point2D(mx,my,x,y,rz);
	FCNPC_SetAngle(npcid,rz);
	return rz;
} 
 
Tryg3D::Function:: FCNPC_SetVehicleRotation(npcid,Float:rx,Float:ry,Float:rz){
	new Float:qw,Float:qx,Float:qy,Float:qz;
	Tryg3D::EulerToQuat(rx,ry,rz,qw,qx,qy,qz);
	FCNPC_SetQuaternion(npcid,qw,qx,qy,qz);
}
 
 
Tryg3D::Function:: bool:FCNPC_SetVehicleTargetRotation(npcid,Float:tx,Float:ty,Float:tz,Float:ry=0.0){
	new Float:x,Float:y,Float:z,Float:rx,Float:rz;
	GetVehiclePos(FCNPC_GetVehicleID(npcid),x,y,z);
	if(GetRotationFor2Point3D(x,y,z,tx,ty,tz,rx,rz)){
		new Float:qw,Float:qx,Float:qy,Float:qz;
		Tryg3D::EulerToQuat(rx,ry,rz,qw,qx,qy,qz);
		FCNPC_SetQuaternion(npcid,qw,qx,qy,qz);
		return true;
	}
	return false;
} 
 
Tryg3D::Function:: FCNPC_GoToAir(npcid,Float:x,Float:y,Float:z,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO){
	FCNPC_SetVehicleTargetRotation(npcid,x,y,z);
	FCNPC_GoTo(npcid,x,y,z,type,speed,false,0.0,false);
} 
 
#if defined Tryg3D_ColAndreas 
 
Tryg3D::Function:: Float:GetPointInFrontOfNPCCol(npcid,&Float:tx,&Float:ty,Float:radius){
	new Float:rz,Float:z;
	FCNPC_GetPosition(npcid,tx,ty,z);
	if(IsPlayerInAnyVehicle(npcid)){
		GetVehicleZAngle(FCNPC_GetVehicleID(npcid),rz);
	} else {
		rz = FCNPC_GetAngle(npcid);
	}
	GetPointInFront3DCol(tx,ty,z,0.0,rz,radius,tx,ty,z);
	return rz;
} 
 
Tryg3D::Function:: FCNPC_GoToCol(npcid,Float:x,Float:y,Float:z,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,Float:cut_size = 0.0,bool:setangle = true){
	new Float:px,Float:py,Float:pz,Float:tx,Float:ty,Float:tz;
	FCNPC_GetPosition(npcid,px,py,pz);
	if(MovePointColCutLineEx(px,py,pz,x,y,z,tx,ty,tz,cut_size)){
		FCNPC_GoTo(npcid,tx,ty,tz,type,speed,UseMapAndreas,0.0,setangle);
	}
} 
 
Tryg3D::Function:: FCNPC_GoToPlayerCol(npcid,playerid,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,Float:cut_size = 0.0,bool:setangle = true){
	new Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz;
	GetPlayerPos(playerid,x,y,z);
	FCNPC_GetPosition(npcid,px,py,pz);
	if(MovePointColCutLineEx(px,py,pz,x,y,z,tx,ty,tz,cut_size)){
		FCNPC_GoTo(npcid,tx,ty,tz,type,speed,UseMapAndreas,0.0,setangle);
	}
} 
 
Tryg3D::Function:: FCNPC_GoToPlayerOnGroundCol(npcid,playerid,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,Float:cut_size = 1.0,Float:climbing = 2.0,bool:setangle = true){
	new Float:px,Float:py,Float:pz,Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz;
	GetPlayerPos(playerid,x,y,z);
	FCNPC_GetPosition(npcid,px,py,pz);
	if(GetDistanceBetweenPoints1D(pz,z) > climbing) z = pz;
	if(MovePointColCutLineEx(px,py,pz,x,y,z,tx,ty,tz,cut_size)){
		FCNPC_GoTo(npcid,tx,ty,tz,type,speed,UseMapAndreas,0.0,setangle);
	}
} 
 
Tryg3D::Function:: FCNPC_GoToAirCol(npcid,Float:x,Float:y,Float:z,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,Float:cut_size = 0.0){
	new Float:px,Float:py,Float:pz,Float:tx,Float:ty,Float:tz;
	GetVehiclePos(FCNPC_GetVehicleID(npcid),px,py,pz);
	if(MovePointColCutLineEx(px,py,pz,x,y,z,tx,ty,tz,cut_size)){
		FCNPC_SetVehicleTargetRotation(npcid,tx,ty,tz);
		FCNPC_GoTo(npcid,tx,ty,tz,type,speed,false,0.0,false);
	}
} 
 
#if defined Tryg3D_Streamer 
 
Tryg3D::Function:: FCNPC_RandomMoveInDynamicArea(npcid,STREAMER_TAG_AREA areaid,Float:climbing = 2.0,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,bool:setangle = true){
	new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:tmp_float; 
	FCNPC_GetPosition(npcid,x,y,z);
	if(!GetRandomPointInDynamicArea(areaid,tx,ty,tz)) return 0;
	CA_FindZ_For2DCoord(tx,ty,tz); 
	while(CA_RayCastLine(x,y,z,tx,ty,tz,tmp_float,tmp_float,tmp_float)){
		GetRandomPointInDynamicArea(areaid,tx,ty,tz);
		CA_FindZ_For2DCoord(tx,ty,tz);
		if(GetDistanceBetweenPoints1D(tz,z) > climbing) continue;
	}
    return FCNPC_GoTo(npcid,tx,ty,tz+1.0,type,speed,UseMapAndreas,0.0,setangle); 
}  
 
#endif 
 
#if defined Tryg3D_Stream3D 
 
Tryg3D::Function:: FCNPC_RandomMoveInStream(npcid,Stream:StreamData[Stream3D],Float:climbing = 2.0,type = MOVE_TYPE_AUTO,Float:speed = MOVE_SPEED_AUTO,bool:UseMapAndreas = false,bool:setangle = true){
	new Float:x,Float:y,Float:z,Float:tx,Float:ty,Float:tz,Float:tmp_float; 
	FCNPC_GetPosition(npcid,x,y,z);
	GetRandomPointInStream(StreamData,tx,ty,tz);
	CA_FindZ_For2DCoord(tx,ty,tz); 
	while(CA_RayCastLine(x,y,z,tx,ty,tz,tmp_float,tmp_float,tmp_float)){
		GetRandomPointInStream(StreamData,tx,ty,tz);
		CA_FindZ_For2DCoord(tx,ty,tz);
		if(GetDistanceBetweenPoints1D(tz,z) > climbing) continue;
	}
    return FCNPC_GoTo(npcid,tx,ty,tz+1.0,type,speed,UseMapAndreas,0.0,setangle); 
}  
 
#endif 
 
#endif 
 
#endif 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * Functions extra names                                                                                                            *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#define GetDistanceBetweenPoints						GetDistanceBetweenPoints3D
#define GetPlayersDistance								GetDistanceBetweenPlayers
#define GetVehiclesDistance								GetDistanceBetweenVehicles
#define GetObjectsDistance								GetDistanceBetweenObjects
 
 
/************************************************************************************************************************************
 *                                                                                                                                  *
 * FilterScript/GameMode Init Hook                                                                                                  *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

new bool:CRC_Tryg3DInit = true,
	bool:CRC_Tryg3DExit = true,
	T3D:FSAT = 0;

#define Tryg3D_GetActiveTime()							(GetTickCount()-T3D:FSAT)

#if defined Tryg3D_ColAndreas

	forward OnColAndreasRemoveBuilding();

	Tryg3D::Function:: bool:Tryg3D::IsColAndreasInit(){
		new Float:mapunit;
		CA_FindZ_For2DCoord(0.0,0.0,mapunit);
		return !(mapunit <= 0.0);
	}

	Tryg3D::Function:: Tryg3D::SafeColAndreasInit(){
		//check ColAndreas Init
		new bool:ColAndreasLastStat = false;
		if(!Tryg3D::IsColAndreasInit()){
			CallLocalFunction("OnColAndreasRemoveBuilding","");
			CA_Init();
			ColAndreasLastStat = true;
		}
		if(!Tryg3D::IsColAndreasInit()){
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Error: ColAndreas failed to initiated.");
				print("[ADM] Error: Cannot load /scriptfiles/colandreas/ColAndreas.cadb");
				Update3DTrygErrorCount();
			}
		} else {
			if(ColAndreasLastStat){
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Info: ColAndreas successfully init.");
				}
			}
		}
	}
	
	#define IsColAndreasInit							Tryg3D::IsColAndreasInit
	#define SafeColAndreasInit 							Tryg3D::SafeColAndreasInit
	
#endif

#if defined Tryg3D_MapAndreas

	Tryg3D::Function:: bool:Tryg3D::IsMapAndreasInit(){
		new Float:mapunit;
		MapAndreas_FindZ_For2DCoord(0.0,0.0,mapunit);
		return !(mapunit <= 0.0);
	}

	//Switch MapAndreas Version
	#if defined MAP_ANDREAS_ERROR_SUCCESS
		//MapAndreas 1.2.1
		Tryg3D::Function:: Tryg3D::SafeMapAndreasInit(mode = MAP_ANDREAS_MODE_FULL, name[]="", len=sizeof(name)){
			//check MapAndreas Init
			new bool:MapAndreasLastStat = false;
			if(!Tryg3D::IsMapAndreasInit()){
				MapAndreas_Init(mode,name,len);
				MapAndreasLastStat = true;
			}
			if(!Tryg3D::IsMapAndreasInit()){
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Error: MapAndreas failed to initiated.");
					print("[ADM] Error: Cannot load /scriptfiles/SAfull.hmap");
					Update3DTrygErrorCount();
				}
			} else {
				if(MapAndreasLastStat){
					if(GetSVarInt("ADM:Logging:Disable") == 0){
						print("[ADM] Info: MapAndreas successfully init.");
					}
				}
			}
		}
	#else
		//MapAndreas 1.1.0
		Tryg3D::Function:: Tryg3D::SafeMapAndreasInit(mode){
			//check MapAndreas Init
			new bool:MapAndreasLastStat = false;
			if(!Tryg3D::IsMapAndreasInit()){
				MapAndreas_Init(mode);
				MapAndreasLastStat = true;
			}
			if(!Tryg3D::IsMapAndreasInit()){
				if(GetSVarInt("ADM:Logging:Disable") == 0){
					print("[ADM] Error: MapAndreas failed to initiated.");
					print("[ADM] Error: Cannot load /scriptfiles/SAfull.hmap");
					Update3DTrygErrorCount();
				}
			} else {
				if(MapAndreasLastStat){
					if(GetSVarInt("ADM:Logging:Disable") == 0){
						print("[ADM] Info: MapAndreas successfully init.");
					}
				}
			}
		}
	#endif
	
#endif

Tryg3D::Function:: Tryg3DInit_MapPrecision(){
	#if defined Tryg3D_ColAndreas
		Tryg3D::SafeColAndreasInit();
	#elseif defined Tryg3D_MapAndreas
		Tryg3D::SafeMapAndreasInit(MAP_ANDREAS_MODE_FULL);
	#else
		
	#endif
}

Tryg3D::Public:: Tryg3D::OnRequestResponse(index, response_code, data[]){
	if(response_code == 200){
		if(isnull(data)) return 0;
		new T3D:version[16], T3D:ver, T3D:file_ver = Tryg3D_Version;
		strmid(T3D:version,data,0,strlen(data));
		T3D:ver = strval(T3D:version);
		if(T3D:ver != T3D:file_ver){
			print(" ");
			printf("[ADM] Info: Please update your 3DTryg include to v%d.%d.%d from here:",(T3D:ver / 10000),((T3D:ver % 10000) / 100),((T3D:ver % 10000) % 100));
			print("https://github.com/AbyssMorgan/SA-MP/blob/master/include/SAM/3DTryg.inc");
			print(" ");
		}
	}
	return 1;
}

Tryg3D::Function:: Tryg3DInit(){
	T3D:FSAT = GetTickCount();
	SetSVarInt("ADM:3DTryg:ACTIVE",Tryg3D::GetActiveCount()+1);
	
	//Welcome to 3DTryg
	new T3D:ver_name[16];
	format(T3D:ver_name,sizeof(T3D:ver_name),"%d.%d.%d",(Tryg3D_Version / 10000),((Tryg3D_Version % 10000) / 100),((Tryg3D_Version % 10000) % 100));
	if(GetSVarInt("ADM:3DTryg:INIT") == 0){
		SetSVarInt("ADM:3DTryg:INIT",1);
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Info: Load 3DTryg v%s for SA:MP %s by Abyss Morgan",T3D:ver_name,Tryg3D_SAMP_Version);
		}
	}
	
	if(GetSVarInt("ADM:3DTryg:VERCHECK") == 0){
		SetSVarInt("ADM:3DTryg:VERCHECK",1);
		new T3D:send_data[50];
		format(T3D:send_data,sizeof(T3D:send_data),"8.ct8.pl/tryg3d/check.php?version=%d",Tryg3D_Version);
		HTTP(0,HTTP_GET,T3D:send_data,"","Tryg3D_OnRequestResponse");
	}
	
	//Init ColAndreas
	#if ((!defined DISABLE_3D_TRYG_CHECK) && (defined Tryg3D_ColAndreas) && (COLANDREAS_VERSION != 0))
		CheckColAndreasVersion();
	#endif
	
	//Init Map Precision
	#if !defined DISABLE_3D_TRYG_INIT
		Tryg3DInit_MapPrecision();
	#endif
	
	//Init YSF Timeline Sync
	#if ((defined Tryg3D_YSF) && (defined ENABLE_3D_TRYG_TIMELINE_SYNC))
		if(GetSVarInt("ADM:3DTryg:YSF:TIMELINE") == 0){
			SetSVarInt("ADM:3DTryg:YSF:TIMELINE",1);
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Info: YSF Timeline Sync successfully init.");
			}
		}
	#endif
	
	//Init Streamer
	#if (!defined DISABLE_3D_TRYG_CHECK && defined Tryg3D_Streamer)
		Tryg3D::CheckStreamerVersion();
		if(GetSVarInt("ADM:3DTryg:Streamer") == 0){
			SetSVarInt("ADM:3DTryg:Streamer",1);
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				if(T3D:Tryg3DStreamerExam){
					print("[ADM] Info: Streamer successfully init.");
				} else {
					print("[ADM] Error: Streamer failed to initiated.");
					Update3DTrygErrorCount();
				}
			}
		}
	#endif
	
	#if defined Tryg3D_Streamer
		#pragma unused v3DTryg3DStreamerExam
	#endif
	
	//Init FCNPC
	#if (!defined DISABLE_3D_TRYG_CHECK && defined Tryg3D_FCNPC)
		#if	(FCNPC_INCLUDE_VERSION < Tryg3D_FCNPC_Version)
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				new T3D:str1[16],T3D:str2[16];
				format(T3D:str1,sizeof(T3D:str1),"%d",FCNPC_INCLUDE_VERSION);
				format(T3D:str2,sizeof(T3D:str2),"%d",Tryg3D_FCNPC_Version);
				printf("[ADM] Error: Your FCNPC %c.%c.%c It is not compatible with this version 3DTryg, update your FCNPC to %c.%c.%c",T3D:str1[0],T3D:str1[1],T3D:str1[2],T3D:str2[0],T3D:str2[1],T3D:str2[2]);
				Update3DTrygErrorCount();
			}
		#else
			if(GetSVarInt("ADM:3DTryg:FCNPC") == 0){
				SetSVarInt("ADM:3DTryg:FCNPC",1);
				print("[ADM] Info: FCNPC successfully init.");
			}
		#endif
	#endif
	
	#if ((defined Tryg3D_MapAndreas) && (defined Tryg3D_FCNPC))
		new T3D:MapAddress = MapAndreas_GetAddress();
		if(T3D:MapAddress != 0){
			FCNPC_InitMapAndreas(T3D:MapAddress);
			if(GetSVarInt("ADM:Logging:Disable") == 0){
				print("[ADM] Info: MapAndreas successfully attached to FCNPC.");
			}
		}
	#endif
}

Tryg3D::Function:: Tryg3DExit(){
	SetSVarInt("ADM:3DTryg:ACTIVE",Tryg3D::GetActiveCount()-1);
	
	//Goodbye 3DTryg
	new T3D:ver_name[16];
	format(T3D:ver_name,sizeof(T3D:ver_name),"%d.%d.%d",(Tryg3D_Version / 10000),((Tryg3D_Version % 10000) / 100),((Tryg3D_Version % 10000) % 100));
	if(Tryg3D::GetActiveCount() == 0){
		SetSVarInt("ADM:3DTryg:INIT",0);
		if(GetSVarInt("ADM:Logging:Disable") == 0){
			printf("[ADM] Info: Unload 3DTryg v%s for SA:MP %s by Abyss Morgan",T3D:ver_name,Tryg3D_SAMP_Version);
		}
	}
}

//Hook: OnFilterScriptInit
public OnFilterScriptInit(){
	if(CRC_Tryg3DInit){
		CRC_Tryg3DInit = false;
		Tryg3DInit();
	}
	#if defined Tryg3D_OnFilterScriptInit
		Tryg3D_OnFilterScriptInit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif
#define OnFilterScriptInit Tryg3D_OnFilterScriptInit
#if defined Tryg3D_OnFilterScriptInit
	forward Tryg3D_OnFilterScriptInit();
#endif

//Hook: OnGameModeInit
public OnGameModeInit(){
	if(CRC_Tryg3DInit){
		CRC_Tryg3DInit = false;
		Tryg3DInit();
	}
	#if defined Tryg3D_OnGameModeInit
		Tryg3D_OnGameModeInit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif
#define OnGameModeInit Tryg3D_OnGameModeInit
#if defined Tryg3D_OnGameModeInit
	forward Tryg3D_OnGameModeInit();
#endif

//Hook: OnFilterScriptExit
public OnFilterScriptExit(){
	if(CRC_Tryg3DExit){
		CRC_Tryg3DExit = false;
		Tryg3DExit();
	}
	#if defined Tryg3D_OnFilterScriptExit
		Tryg3D_OnFilterScriptExit();
	#endif
	return 1;
}

#if defined _ALS_OnFilterScriptExit
	#undef OnFilterScriptExit
#else
	#define _ALS_OnFilterScriptExit
#endif
#define OnFilterScriptExit Tryg3D_OnFilterScriptExit
#if defined Tryg3D_OnFilterScriptExit
	forward Tryg3D_OnFilterScriptExit();
#endif

//Hook: OnGameModeExit
public OnGameModeExit(){
	if(CRC_Tryg3DExit){
		CRC_Tryg3DExit = false;
		Tryg3DExit();
	}
	#if defined Tryg3D_OnGameModeExit
		Tryg3D_OnGameModeExit();
	#endif
	return 1;
}

#if defined _ALS_OnGameModeExit
	#undef OnGameModeExit
#else
	#define _ALS_OnGameModeExit
#endif
#define OnGameModeExit Tryg3D_OnGameModeExit
#if defined Tryg3D_OnGameModeExit
	forward Tryg3D_OnGameModeExit();
#endif

/************************************************************************************************************************************
 *                                                                                                                                  *
 * Additional operations                                                                                                            *
 *                                                                                                                                  *
 ************************************************************************************************************************************/

#pragma unused Tryg3D_WeaponDamage
#pragma unused Tryg3D_StreamDistance
#pragma unused v3DFSAT

#undef Update3DTrygErrorCount

//EOF 
 
