FIND_PATH(mRss_INCLUDE_DIRS mrss.h)

SET(mRss_NAMES ${mRss_NAMES} mrss)
FIND_LIBRARY(mRss_LIBRARIES NAMES ${mRss_NAMES} )

# handle the QUIETLY and REQUIRED arguments and set mRss_FOUND to TRUE if 
# all listed variables are TRUE
INCLUDE( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS(mRss DEFAULT_MSG mRss_LIBRARIES mRss_INCLUDE_DIRS)

MARK_AS_ADVANCED(mRss_LIBRARIES mRss_INCLUDE_DIRS )
