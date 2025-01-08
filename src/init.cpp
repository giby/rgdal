#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

// Include only C headers here
#include <stdlib.h>
#include <string.h>
#include "rgdal.h"

// Declare the functions you want to expose to R here
extern "C" {
    void RGDAL_Init();
    void RGDAL_Exit();
    SEXP RGDAL_checkCRSArgs(SEXP);
    SEXP RGDAL_GetDescription(SEXP);
    SEXP RGDAL_GDALVersionInfo(SEXP);
    SEXP RGDAL_GDALCheckVersion();
    SEXP RGDAL_GDALwithGEOS();
    SEXP RGDAL_GDAL_DATA_Info();
    SEXP RGDAL_GetDriverNames();
    SEXP RGDAL_GetDriver(SEXP);
    SEXP RGDAL_GetDriverShortName(SEXP);
    SEXP RGDAL_GetDriverLongName(SEXP);
    SEXP RGDAL_OpenDataset(SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP RGDAL_CloseHandle(SEXP);
    SEXP RGDAL_CreateDataset(SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP RGDAL_GetDatasetDriver(SEXP);
    SEXP RGDAL_CopyDataset(SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP RGDAL_DeleteFile(SEXP, SEXP);
    SEXP RGDAL_CloseDataset(SEXP);
    SEXP RGDAL_GetRasterYSize(SEXP);
    SEXP RGDAL_GetRasterXSize(SEXP);
    SEXP RGDAL_GetRasterCount(SEXP);
    SEXP RGDAL_GetProjectionRef(SEXP, SEXP);
    SEXP RGDAL_PutRasterData(SEXP, SEXP, SEXP);
    SEXP RGDAL_GetRasterData(SEXP, SEXP, SEXP, SEXP);
    SEXP RGDAL_GetScale(SEXP);
    SEXP RGDAL_GetOffset(SEXP);
    SEXP RGDAL_GetCategoryNames(SEXP);
    SEXP RGDAL_GetColorTable(SEXP);
    SEXP RGDAL_GetColorInterp(SEXP);
    SEXP RGDAL_GetPaletteInterp(SEXP);
    SEXP RGDAL_GenCMap(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP RGDAL_GetRasterBand(SEXP, SEXP);
    SEXP RGDAL_GetYSize(SEXP);
    SEXP RGDAL_GetXSize(SEXP);
    SEXP RGDAL_GetGeoTransform(SEXP);
    SEXP RGDAL_GetRasterBlockSize(SEXP);
    SEXP RGDAL_CPLGetConfigOption(SEXP);
    SEXP RGDAL_CPLSetConfigOption(SEXP, SEXP);
    SEXP RGDAL_CPL_RECODE_ICONV();
    SEXP PROJcopyEPSG(SEXP);
    SEXP RGDAL_ogrInfo(SEXP, SEXP);
    SEXP R_OGR_types(SEXP, SEXP);
    SEXP RGDAL_ogrFIDs(SEXP, SEXP);
    SEXP ogr_GetDriverNames();
    SEXP ogrP4S(SEXP, SEXP, SEXP, SEXP);
    SEXP RGDAL_ogrListLayers(SEXP);
    SEXP ogrDataFrame(SEXP, SEXP, SEXP, SEXP);
    SEXP R_OGR_CAPI_features(SEXP, SEXP, SEXP);
    SEXP make_Polygonlist(SEXP, SEXP);
    SEXP p4s_to_wkt(SEXP, SEXP);
    SEXP wkt_to_p4s(SEXP, SEXP);
    SEXP P6_SRID_show(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP P6_SRID_proj(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP list_coordinate_ops(SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP ogrAutoIdentifyEPSG(SEXP);
    SEXP OGR_write(SEXP);
    SEXP RGDAL_ogrDeleteLayer(SEXP, SEXP, SEXP);
    SEXP RGDAL_ogrDeleteDataSource(SEXP, SEXP);
    SEXP ogrCheckExists(SEXP, SEXP);
    SEXP R_GDAL_OSR_PROJ();
    SEXP PROJ4VersionInfo();
    SEXP PROJ4NADsInstalled();
    SEXP get_proj_search_path();
    SEXP get_proj_user_writable_dir();
    SEXP set_proj_paths(SEXP);
    SEXP PROJ4_proj_def_dat_Installed();
    SEXP transform(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP transform_ng(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP RGDAL_projInfo(SEXP);
    SEXP RGDAL_project(SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP project_inv(SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP project_ng(SEXP, SEXP, SEXP, SEXP, SEXP);
    SEXP project_ng_coordOp(SEXP, SEXP, SEXP, SEXP);
    SEXP CRS_compare(SEXP, SEXP, SEXP, SEXP);
    SEXP proj_network_enabled();
    SEXP enable_proj_network();
    SEXP disable_proj_network();
    SEXP get_source_crs(SEXP);
    SEXP proj_vis_order(SEXP);
    SEXP OSR_is_projected(SEXP);
    SEXP RGDAL_SetGeoTransform(SEXP, SEXP);
    SEXP RGDAL_GetNoDataValue(SEXP);
    SEXP RGDAL_GetMetadata(SEXP, SEXP);
    SEXP RGDAL_GetBandType(SEXP);
    SEXP RGDAL_GetBandStatistics(SEXP, SEXP);
    SEXP RGDAL_GetBandMinimum(SEXP);
    SEXP RGDAL_GetBandMaximum(SEXP);
    SEXP RGDAL_GetRAT(SEXP);
    SEXP RGDAL_GetBandNoDataValue(SEXP);
    SEXP RGDAL_SetProject(SEXP, SEXP);
    SEXP RGDAL_SetProject_WKT2(SEXP, SEXP, SEXP);
    SEXP RGDAL_SetNoDataValue(SEXP, SEXP);
    SEXP RGDAL_SetStatistics(SEXP, SEXP);
    SEXP RGDAL_SetRasterColorTable(SEXP, SEXP, SEXP, SEXP);
    SEXP RGDAL_SetCategoryNames(SEXP, SEXP);
    SEXP isGDALObjPtrNULL(SEXP);
    SEXP rgdal_sp_linkingTo_version();
}

static R_CallMethodDef CallEntries[] = {
    {"RGDAL_Init", (DL_FUNC) &RGDAL_Init, 0},
    {"RGDAL_Exit", (DL_FUNC) &RGDAL_Exit, 0},
    {"RGDAL_checkCRSArgs", (DL_FUNC) &RGDAL_checkCRSArgs, 1},
    {"RGDAL_GetDescription", (DL_FUNC) &RGDAL_GetDescription, 1},
    {"RGDAL_GDALVersionInfo", (DL_FUNC) &RGDAL_GDALVersionInfo, 1},
    {"RGDAL_GDALCheckVersion", (DL_FUNC) &RGDAL_GDALCheckVersion, 0},
    {"RGDAL_GDALwithGEOS", (DL_FUNC) &RGDAL_GDALwithGEOS, 0},
    {"RGDAL_GDAL_DATA_Info", (DL_FUNC) &RGDAL_GDAL_DATA_Info, 0},
    {"RGDAL_GetDriverNames", (DL_FUNC) &RGDAL_GetDriverNames, 0},
    {"RGDAL_GetDriver", (DL_FUNC) &RGDAL_GetDriver, 1},
    {"RGDAL_GetDriverShortName", (DL_FUNC) &RGDAL_GetDriverShortName, 1},
    {"RGDAL_GetDriverLongName", (DL_FUNC) &RGDAL_GetDriverLongName, 1},
    {"RGDAL_OpenDataset", (DL_FUNC) &RGDAL_OpenDataset, 5},
    {"RGDAL_CloseHandle", (DL_FUNC) &RGDAL_CloseHandle, 1},
    {"RGDAL_CreateDataset", (DL_FUNC) &RGDAL_CreateDataset, 5},
    {"RGDAL_GetDatasetDriver", (DL_FUNC) &RGDAL_GetDatasetDriver, 1},
    {"RGDAL_CopyDataset", (DL_FUNC) &RGDAL_CopyDataset, 5},
    {"RGDAL_DeleteFile", (DL_FUNC) &RGDAL_DeleteFile, 2},
    {"RGDAL_CloseDataset", (DL_FUNC) &RGDAL_CloseDataset, 1},
    {"RGDAL_GetRasterYSize", (DL_FUNC) &RGDAL_GetRasterYSize, 1},
    {"RGDAL_GetRasterXSize", (DL_FUNC) &RGDAL_GetRasterXSize, 1},
    {"RGDAL_GetRasterCount", (DL_FUNC) &RGDAL_GetRasterCount, 1},
    {"RGDAL_GetProjectionRef", (DL_FUNC) &RGDAL_GetProjectionRef, 2},
    {"RGDAL_PutRasterData", (DL_FUNC) &RGDAL_PutRasterData, 3},
    {"RGDAL_GetRasterData", (DL_FUNC) &RGDAL_GetRasterData, 4},
    {"RGDAL_GetScale", (DL_FUNC) &RGDAL_GetScale, 1},
    {"RGDAL_GetOffset", (DL_FUNC) &RGDAL_GetOffset, 1},
    {"RGDAL_GetCategoryNames", (DL_FUNC) &RGDAL_GetCategoryNames, 1},
    {"RGDAL_GetColorTable", (DL_FUNC) &RGDAL_GetColorTable, 1},
    {"RGDAL_GetColorInterp", (DL_FUNC) &RGDAL_GetColorInterp, 1},
    {"RGDAL_GetPaletteInterp", (DL_FUNC) &RGDAL_GetPaletteInterp, 1},
    {"RGDAL_GenCMap", (DL_FUNC) &RGDAL_GenCMap, 6},
    {"RGDAL_GetRasterBand", (DL_FUNC) &RGDAL_GetRasterBand, 2},
    {"RGDAL_GetYSize", (DL_FUNC) &RGDAL_GetYSize, 1},
    {"RGDAL_GetXSize", (DL_FUNC) &RGDAL_GetXSize, 1},
    {"RGDAL_GetGeoTransform", (DL_FUNC) &RGDAL_GetGeoTransform, 1},
    {"RGDAL_GetRasterBlockSize", (DL_FUNC) &RGDAL_GetRasterBlockSize, 1},
    {"RGDAL_CPLGetConfigOption", (DL_FUNC) &RGDAL_CPLGetConfigOption, 1},
    {"RGDAL_CPLSetConfigOption", (DL_FUNC) &RGDAL_CPLSetConfigOption, 2},
    {"RGDAL_CPL_RECODE_ICONV", (DL_FUNC) &RGDAL_CPL_RECODE_ICONV, 0},
    {"PROJcopyEPSG", (DL_FUNC) &PROJcopyEPSG, 1},
    {"RGDAL_ogrInfo", (DL_FUNC) &RGDAL_ogrInfo, 2},
    {"R_OGR_types", (DL_FUNC) &R_OGR_types, 2},
    {"RGDAL_ogrFIDs", (DL_FUNC) &RGDAL_ogrFIDs, 2},
    {"ogr_GetDriverNames", (DL_FUNC) &ogr_GetDriverNames, 0},
    {"ogrP4S", (DL_FUNC) &ogrP4S, 4},
    {"RGDAL_ogrListLayers", (DL_FUNC) &RGDAL_ogrListLayers, 1},
    {"ogrDataFrame", (DL_FUNC) &ogrDataFrame, 4},
    {"R_OGR_CAPI_features", (DL_FUNC) &R_OGR_CAPI_features, 3},
    {"make_Polygonlist", (DL_FUNC) &make_Polygonlist, 2},
    {"p4s_to_wkt", (DL_FUNC) &p4s_to_wkt, 2},
    {"wkt_to_p4s", (DL_FUNC) &wkt_to_p4s, 2},
    {"P6_SRID_show", (DL_FUNC) &P6_SRID_show, 6},
    {"P6_SRID_proj", (DL_FUNC) &P6_SRID_proj, 6},
    {"list_coordinate_ops", (DL_FUNC) &list_coordinate_ops, 5},
    {"ogrAutoIdentifyEPSG", (DL_FUNC) &ogrAutoIdentifyEPSG, 1},
    {"OGR_write", (DL_FUNC) &OGR_write, 1},
    {"RGDAL_ogrDeleteLayer", (DL_FUNC) &RGDAL_ogrDeleteLayer, 3},
    {"RGDAL_ogrDeleteDataSource", (DL_FUNC) &RGDAL_ogrDeleteDataSource, 2},
    {"ogrCheckExists", (DL_FUNC) &ogrCheckExists, 2},
    {"R_GDAL_OSR_PROJ", (DL_FUNC) &R_GDAL_OSR_PROJ, 0},
    {"PROJ4VersionInfo", (DL_FUNC) &PROJ4VersionInfo, 0},
    {"PROJ4NADsInstalled", (DL_FUNC) &PROJ4NADsInstalled, 0},
    {"get_proj_search_path", (DL_FUNC) &get_proj_search_path, 0},
    {"get_proj_user_writable_dir", (DL_FUNC) &get_proj_user_writable_dir, 0},
    {"set_proj_paths", (DL_FUNC) &set_proj_paths, 1},
    {"PROJ4_proj_def_dat_Installed", (DL_FUNC) &PROJ4_proj_def_dat_Installed, 0},
    {"transform", (DL_FUNC) &transform, 6},
    {"transform_ng", (DL_FUNC) &transform_ng, 8},
    {"RGDAL_projInfo", (DL_FUNC) &RGDAL_projInfo, 1},
    {"RGDAL_project", (DL_FUNC) &RGDAL_project, 5},
    {"project_inv", (DL_FUNC) &project_inv, 5},
    {"project_ng", (DL_FUNC) &project_ng, 5},
    {"project_ng_coordOp", (DL_FUNC) &project_ng_coordOp, 4},
    {"CRS_compare", (DL_FUNC) &CRS_compare, 4},
    {"proj_network_enabled", (DL_FUNC) &proj_network_enabled, 0},
    {"enable_proj_network", (DL_FUNC) &enable_proj_network, 0},
    {"disable_proj_network", (DL_FUNC) &disable_proj_network, 0},
    {"get_source_crs", (DL_FUNC) &get_source_crs, 1},
    {"proj_vis_order", (DL_FUNC) &proj_vis_order, 1},
    {"OSR_is_projected", (DL_FUNC) &OSR_is_projected, 1},
    {"RGDAL_SetGeoTransform", (DL_FUNC) &RGDAL_SetGeoTransform, 2},
    {"RGDAL_GetNoDataValue", (DL_FUNC) &RGDAL_GetNoDataValue, 1},
    {"RGDAL_GetMetadata", (DL_FUNC) &RGDAL_GetMetadata, 2},
    {"RGDAL_GetBandType", (DL_FUNC) &RGDAL_GetBandType, 1},
    {"RGDAL_GetBandStatistics", (DL_FUNC) &RGDAL_GetBandStatistics, 2},
    {"RGDAL_GetBandMinimum", (DL_FUNC) &RGDAL_GetBandMinimum, 1},
    {"RGDAL_GetBandMaximum", (DL_FUNC) &RGDAL_GetBandMaximum, 1},
    {"RGDAL_GetRAT", (DL_FUNC) &RGDAL_GetRAT, 1},
    {"RGDAL_GetBandNoDataValue", (DL_FUNC) &RGDAL_GetBandNoDataValue, 1},
    {"RGDAL_SetProject", (DL_FUNC) &RGDAL_SetProject, 2},
    {"RGDAL_SetProject_WKT2", (DL_FUNC) &RGDAL_SetProject_WKT2, 3},
    {"RGDAL_SetNoDataValue", (DL_FUNC) &RGDAL_SetNoDataValue, 2},
    {"RGDAL_SetStatistics", (DL_FUNC) &RGDAL_SetStatistics, 2},
    {"RGDAL_SetRasterColorTable", (DL_FUNC) &RGDAL_SetRasterColorTable, 4},
    {"RGDAL_SetCategoryNames", (DL_FUNC) &RGDAL_SetCategoryNames, 2},
    {"isGDALObjPtrNULL", (DL_FUNC) &isGDALObjPtrNULL, 1},
    {"rgdal_sp_linkingTo_version", (DL_FUNC) &rgdal_sp_linkingTo_version, 0},
    {NULL, NULL, 0}
};

static const R_CMethodDef CEntries[] = {
    {NULL, NULL, 0}
};

void R_init_rgdal(DllInfo *dll) {
    R_registerRoutines(dll, CEntries, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, static_cast<Rboolean>(FALSE));
}
