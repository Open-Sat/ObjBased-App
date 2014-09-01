/*########################### Remove This Comment Block #######################
** This a template file and has been designed to allow the template variables 
** _template_ and _exobj_ to be automatically replaced.  See template.h for
** template instantiation guidelines.
#############################################################################*/
/*
** $Id: $
** 
** Purpose: Define configurations for the _Template_ application
**
** Notes:
**   1. These macros can only be built with the application and can't
**      have a platform scope because the same file name is used for
**      all applications following the object-based application design.
**
** References:
**   1. OpenSat Object-based Application Developers Guide.
**
** $Date: $
** $Revision: $
** $Log: $
**
*/

#ifndef _app_config_
#define _app_config_

/*
** Includes
*/

#include "_template__mission_cfg.h"
#include "_template__platform_cfg.h"

/******************************************************************************
** _Template_ Application Macros
*/

#define  _TEMPLATE__MAJOR_VERSION      1
#define  _TEMPLATE__MINOR_VERSION      0
#define  _TEMPLATE__REVISION           0
#define  _TEMPLATE__MISSION_REV        0

#define  _TEMPLATE__RUNLOOP_DELAY    500  /* Delay in milliseconds */

#define  _TEMPLATE__EXOBJ_TBL_DEF_LOAD_FILE  "/ram/exobjtbl.xml"
#define  _TEMPLATE__EXOBJ_TBL_DEF_DUMP_FILE  "/ram/exobjtbl.txt"

/******************************************************************************
** Command Macros
*/

#define _TEMPLATE__CMD_RESET_FC            0
#define _TEMPLATE__CMD_NOOP_FC             1

#define _TEMPLATE__CMD_EXOBJ_TBL_LOAD_FC   2
#define _TEMPLATE__CMD_EXOBJ_TBL_DUMP_FC   3
#define _TEMPLATE__CMD_ENA_DATA_LOAD_FC    4
#define _TEMPLATE__CMD_SET_TBL_INDEX_FC    5

#define CMDMGR_CMD_FUNC_TOTAL   6
#define CMDMGR_PIPE_DEPTH       10
#define CMDMGR_PIPE_NAME        "_TEMPLATE__CMD_PIPE"
#define CMDMGR_CMD_MSG_TOTAL    2

/******************************************************************************
** Event Macros
** 
** Define the base event message IDs used by each object/component used by the
** application. There are no automated checks to ensure an ID range is not
** exceeded so it is the developer's responsibility to verify the ranges. 
*/

#define _TEMPLATE__BASE_EID    0  /* _Template_ application base ID */
#define CMDMGR_BASE_EID  10       /* cmdmgr object base ID  */
#define TBLMGR_BASE_EID  20       /* tblmgr object base ID  */
#define EXOBJ_BASE_EID    30      /* exobj base ID */


/******************************************************************************
** EXOBJ Configurations
**
** Define anything that requires to be configured at the application scope.
*/

#define EXOBJ_TBL_MAX_ENTRY_ID 32

#endif /* _app_config_ */
