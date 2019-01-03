#include "SafeControl.h"
/***********************************************************************************************
*函 数 名: Safety_Protection
*功能说明: 侧倾保护
*形    参: 无
*返 回 值: 无
************************************************************************************************/
void Roll_Protection(void){
	Vector3angle_t Attitude = GetCopterAngle();
	//角度大于35度直接关闭浆叶
	if(Attitude.pitch * 180/PI > 35.0f || Attitude.pitch * 180/PI < -35.0f 
				|| Attitude.roll * 180/PI > 35.0f || Attitude.roll * 180/PI < -35.0f){
		//只有在飞行状态下有用，平衡实验时无用
		if(GetCopterTest() == Drone_Mode_4Axis){
			PWM_OUTPUT(0,0,0,0);
			SetCopterStatus(Drone_Off);
		}
	}
}

/**********************************************************************************************************
*函 数 名: LowPowerProtect
*功能说明: 低电量/电压保护
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
static void LowPowerProtect(void){
	//严重低电量时直接降落
	if(GetBatteryStatus() == BATTERY_LOW){
//		SetCopterStatus(Drone_Land);
	}
}


/**********************************************************************************************************
*函 数 名: SafeControl
*功能说明: 安全保护控制
*形    参: 无
*返 回 值: 无
**********************************************************************************************************/
void SafeControl(void){
    //侧倾保护
    Roll_Protection();

    //低电量/电压保护
    LowPowerProtect();

}

