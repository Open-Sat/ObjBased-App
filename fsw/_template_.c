/*########################### Start Template Block ############################
** This a template file and has been designed to allow template variables to
** be automatically replaced.  See _template_.h for details.
############################# End Template Block ############################*/
/* 
** File:
**   $Id: $
**
** Purpose: Implement the _template_ application.
**
** Notes:
**   1.
**
** References:
**   1. CFS C Coding Standards
**   2. OpenSat Object-based Application Developers Guide.
**
** $Date: $
** $Revision: $
** $Log: $
**
*/

/*
** Includes
*/

#include <string.h>
#include "_template_.h"


/*
** Local Function Prototypes
*/

static int32 InitApp(void);
static void ProcessCommands(void);

/*
** Global Data
*/

_TEMPLATE__Class  _Template_;
_TEMPLATE__HkPkt  _Template_HkPkt;

/******************************************************************************
** Function: _TEMPLATE__Main
**
*/
void _TEMPLATE__Main(void)
{

   int32  Status    = CFE_SEVERITY_ERROR;
   uint32 RunStatus = CFE_ES_APP_ERROR;


   Status = CFE_ES_RegisterApp();
   CFE_EVS_Register(NULL,0,0);

   /*
   ** Perform application specific initialization
   */
   if (Status == CFE_SUCCESS)
   {
       Status = InitApp();
   }

   /*
   ** At this point many flight apps use CFE_ES_WaitForStartupSync() to
   ** synchronize their startup timing with other apps. This is not
   ** needed.
   */

   if (Status == CFE_SUCCESS) RunStatus = CFE_ES_APP_RUN;

   /*
   ** Main process loop
   */
   while (CFE_ES_RunLoop(&RunStatus))
   {

      /*
      ** This is just a an example loop. There are many ways to control the
      ** main loop execution.
      */

      OS_TaskDelay(_TEMPLATE__RUNLOOP_DELAY);

      EXOBJ_LoadDataFromTable();

      ProcessCommands();

   } /* End CFE_ES_RunLoop */


   /* Write to system log in case events not working */

   CFE_ES_WriteToSysLog("_TEMPLATE_ Terminating, RunLoop status = 0x%08X\n", RunStatus);

   CFE_EVS_SendEvent(_TEMPLATE__EXIT_ERR_EID, CFE_EVS_CRITICAL, "_TEMPLATE_ Terminating,  RunLoop status = 0x%08X", RunStatus);

   CFE_ES_ExitApp(RunStatus);  /* Let cFE kill the task (and any child tasks) */

} /* End of _TEMPLATE__Main() */


/******************************************************************************
** Function: _TEMPLATE__NoOpCmd
**
*/

boolean _TEMPLATE__NoOpCmd(const CFE_SB_MsgPtr_t MsgPtr)
{

   CFE_EVS_SendEvent (_TEMPLATE__CMD_NOOP_INFO_EID,
                      CFE_EVS_INFORMATION,
                      "No operation command received for _TEMPLATE_ version %d.%d",
                      _TEMPLATE__MAJOR_VERSION,_TEMPLATE__MINOR_VERSION);

   return TRUE;


} /* End _TEMPLATE__NoOpCmd() */


/******************************************************************************
** Function: _TEMPLATE__ResetAppCmd
**
*/

boolean _TEMPLATE__ResetAppCmd(const CFE_SB_MsgPtr_t MsgPtr)
{

   CMDMGR_ResetStatus();
   TBLMGR_ResetStatus();
   EXOBJ_ResetStatus();

   return TRUE;

} /* End _TEMPLATE__ResetAppCmd() */


/******************************************************************************
** Function: _TEMPLATE__SendHousekeepingPkt
**
*/
void _TEMPLATE__SendHousekeepingPkt(void)
{

   /*
   ** CMDMGR Data
   */

   _Template_HkPkt.ValidCmdCnt   = _Template_.CmdMgr.ValidCmdCnt;
   _Template_HkPkt.InvalidCmdCnt = _Template_.CmdMgr.InvalidCmdCnt;

   /*
   ** TBLMGR Data
   */

   _Template_HkPkt.ExObjTblLoadActive     = _Template_.TblMgr.ExObjTbl.LoadActive;
   _Template_HkPkt.ExObjTblLastLoadValid  = _Template_.TblMgr.ExObjTbl.LastLoadValid;
   _Template_HkPkt.ExObjTblAttrErrCnt     = _Template_.TblMgr.ExObjTbl.AttrErrCnt;

   /*
   ** OBJECT Data
   ** - At a minimum all OBJECT variables effected by a reset must be included
   */

   _Template_HkPkt.EnableDataLoad = _Template_.ExObj.EnableDataLoad;
   _Template_HkPkt.Spare          = 0;
   _Template_HkPkt.TblIndex       = _Template_.ExObj.TblIndex;
   _Template_HkPkt.Data1          = _Template_.ExObj.Data1;
   _Template_HkPkt.Data2          = _Template_.ExObj.Data2;
   _Template_HkPkt.Data3          = _Template_.ExObj.Data3;

   CFE_SB_TimeStampMsg((CFE_SB_Msg_t *) &_Template_HkPkt);
   CFE_SB_SendMsg((CFE_SB_Msg_t *) &_Template_HkPkt);

} /* End _TEMPLATE__SendHousekeepingPkt() */


/******************************************************************************
** Function: InitApp
**
*/
static int32 InitApp(void)
{
    int32 Status = CFE_SUCCESS;

    /*
    ** Initialize 'entity' objects
    */

    EXOBJ_Constructor(&_Template_.ExObj);

    /*
    ** Initialize application managers
    */

    TBLMGR_Constructor(&_Template_.TblMgr, _TEMPLATE__EXOBJ_TBL_DEF_LOAD_FILE);

    CFE_SB_CreatePipe(&_Template_.CmdPipe, CMDMGR_PIPE_DEPTH, CMDMGR_PIPE_NAME);
    CFE_SB_Subscribe(_TEMPLATE__CMD_MID, _Template_.CmdPipe);
    CFE_SB_Subscribe(_TEMPLATE__SEND_HK_MID, _Template_.CmdPipe);

    CMDMGR_Constructor(&_Template_.CmdMgr);
    CMDMGR_RegisterFunc(_TEMPLATE__CMD_RESET_FC,           _TEMPLATE__ResetAppCmd,        0);
    CMDMGR_RegisterFunc(_TEMPLATE__CMD_NOOP_FC,            _TEMPLATE__NoOpCmd,            0);
    CMDMGR_RegisterFunc(_TEMPLATE__CMD_EXOBJ_TBL_LOAD_FC,  TBLMGR_LoadExObjTableCmd,   TBLMGR_LOAD_TBL_CMD_DATA_LEN);
    CMDMGR_RegisterFunc(_TEMPLATE__CMD_EXOBJ_TBL_DUMP_FC,  TBLMGR_DumpExObjTableCmd,   TBLMGR_DUMP_TBL_CMD_DATA_LEN);
    CMDMGR_RegisterFunc(_TEMPLATE__CMD_ENA_DATA_LOAD_FC,   EXOBJ_EnableDataLoadCmd,    EXOBJ_ENABLE_DATA_LOAD_CMD_DATA_LEN);
    CMDMGR_RegisterFunc(_TEMPLATE__CMD_SET_TBL_INDEX_FC,   EXOBJ_SetTblIndexCmd,       EXOBJ_SET_TBL_INDEX_CMD_DATA_LEN);

    CFE_SB_InitMsg(&_Template_HkPkt, _TEMPLATE__TLM_HK_MID, _TEMPLATE__TLM_HK_LEN, TRUE);

    /*
    ** Application startup event message
    */
    Status = CFE_EVS_SendEvent(_TEMPLATE__INIT_INFO_EID,
                               CFE_EVS_INFORMATION,
                               "_TEMPLATE_ Initialized. Version %d.%d.%d.%d",
                               _TEMPLATE__MAJOR_VERSION,
                               _TEMPLATE__MINOR_VERSION,
                               _TEMPLATE__REVISION,
                               _TEMPLATE__MISSION_REV);

    return(Status);

} /* End of InitApp() */


/******************************************************************************
** Function: ProcessCommands
**
*/
static void ProcessCommands(void)
{

   int32           Status;
   CFE_SB_Msg_t*   CmdMsgPtr;
   CFE_SB_MsgId_t  MsgId;

   Status = CFE_SB_RcvMsg(&CmdMsgPtr, _Template_.CmdPipe, CFE_SB_POLL);

   if (Status == CFE_SUCCESS)
   {

      MsgId = CFE_SB_GetMsgId(CmdMsgPtr);

      switch (MsgId)
      {
         case _TEMPLATE__CMD_MID:
            CMDMGR_DispatchFunc(CmdMsgPtr);
            break;

         case _TEMPLATE__SEND_HK_MID:
            _TEMPLATE__SendHousekeepingPkt();
            break;

         default:
            CFE_EVS_SendEvent(_TEMPLATE__CMD_INVALID_MID_ERR_EID, CFE_EVS_ERROR,
                              "Received invalid command packet,MID = 0x%4X",MsgId);

            break;

      } /* End Msgid switch */

   } /* End if SB received a packet */

} /* End ProcessCommands() */


/* end of file */
