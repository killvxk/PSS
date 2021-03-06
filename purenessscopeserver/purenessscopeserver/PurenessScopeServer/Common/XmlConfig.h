#pragma once

#include "define.h"
#include "XmlOpeation.h"

//main.xml配置枚举

/*1.枚举值以复数s结束的可能该类型有多个，并作为数组元素
2.需要增加枚举必须从 MIN到MAX区间范围添加
3.同文件的枚举必须相连*/

enum XmlStart
{
	XML_Config_MIN = 0
};

enum XmlConfig
{
	/*******************main.xml************************/

	/********网络设置********/
	XML_Config_RecvInfo = XML_Config_MIN,
	XML_Config_SendInfo,
	XML_Config_NetWorkMode,
	XML_Config_TCPServerIPs,
	/********连接信息********/
	XML_Config_ConnectServer,
	XML_Config_ClientInfo,
	/********模块设置********/
	XML_Config_ModuleInfos,
	XML_Config_ModuleMangager,
	/********监控信息********/
	XML_Config_Monitor,
	XML_Config_ThreadInfoAI,
	XML_Config_ThreadInfo,
	XML_Config_Console,
	XML_Config_ConsoleKeys,
	/********文件记录********/
	XML_Config_AceDebug,
	XML_Config_CommandAccount,
	XML_Config_CoreSetting,
	/********服务器属性********/
	XML_Config_ServerType,
	XML_Config_ServerID,
	XML_Config_ServerName,
	XML_Config_ServerVersion,
	/********消息设置********/
	XML_Config_PacketParses,
	XML_Config_BuffPacket,
	XML_Config_Message,

	/****************alert.xml*****************/
	XML_Config_AlertConnect,
	XML_Config_IP,
	XML_Config_ClientData,
	XML_Config_CommandInfo,
	XML_Config_Mail,
	XML_Config_WorkThreadChart,
	XML_Config_ConnectChart,
	XML_Config_CommandChart,

	/*枚举结束*/
	XML_Config_End
};

enum XmlEnd
{
	XML_Config_MAX = XML_Config_End
};

class IConfigOpeation;

//MianConfig主类
class XMainConfig
{
public:
	XMainConfig() { Init(); }
	bool Init();
	template<class T>
	T* GetXmlConfig();
private:
	bool InitFile(const char* pFileName, XmlConfig start, XmlConfig end);
	CXmlOpeation m_XmlOpeation;
};

typedef ACE_Singleton<XMainConfig, ACE_Null_Mutex> App_XmlConfig;

#define GetXmlConfigAttribute(XmlClass) App_XmlConfig::instance()->GetXmlConfig<XmlClass>()

class IConfigOpeation
{
	friend class XMainConfig;
public:
	virtual ~IConfigOpeation() {}
protected:
	IConfigOpeation(XmlConfig config)
	{
		_array[config] = this;
	}
	virtual bool Init(CXmlOpeation* pXmlOpeation) = 0;
private:
	static IConfigOpeation* _array[XML_Config_MAX];
};



//接收数据包连接相关设置
class xmlRecvInfo : public IConfigOpeation
{
public:
	uint32 RecvBuffSize;
	uint16 RecvQueueTimeout;
	xmlRecvInfo(XmlConfig config) : IConfigOpeation(config), RecvBuffSize(0), RecvQueueTimeout(0) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

//发送数据包连接相关设置
class xmlSendInfo : public IConfigOpeation
{
public:
	uint16 SendQueueMax;//发送队列中最长的数据包个数
	uint16 TcpNodelay;
	uint32 MaxBlockSize;
	uint32 SendDatamark;
	uint32 BlockCount;
	uint16 SendTimeout;
	uint16 SendQueueTimeout;
	uint16 SendQueueCount;
	uint16 PutQueueTimeout;
	xmlSendInfo(XmlConfig config) : IConfigOpeation(config), SendQueueMax(0), TcpNodelay(TCP_NODELAY_OFF), MaxBlockSize(0),
		SendDatamark(0), BlockCount(0), SendTimeout(0), SendQueueTimeout(0), SendQueueCount(0), PutQueueTimeout(0) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

//网络模型
class xmlNetWorkMode : public IConfigOpeation
{
public:
	uint8 Mode;
	uint16 BackLog;
	uint8 ByteOrder;
	xmlNetWorkMode(XmlConfig config) : IConfigOpeation(config), Mode(0), BackLog(0), ByteOrder(false) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlTCPServerIPs : public IConfigOpeation
{
public:
	class _TCPServerIP
	{
	public:
		string ip;
		uint32 port;
		_TCPServerIP() : ip(""), port(0){}
	};
	std::vector<_TCPServerIP> vec;
	xmlTCPServerIPs(XmlConfig config) : IConfigOpeation(config) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlConnectServer : public IConfigOpeation
{
public:
	uint32 TimeInterval;
	uint32 Recvbuff;
	uint8 RunType;
	uint16 TimeCheck;
	uint16 Count;
	xmlConnectServer(XmlConfig config) : IConfigOpeation(config), TimeInterval(500), Recvbuff(1024), RunType(0), Count(100) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlClientInfo : public IConfigOpeation
{
public:
	uint32 HandlerCount;
	uint32 MaxHandlerCount;
	uint16 MaxConnectTime;
	uint16 CheckAliveTime;
	uint32 MaxBuffRecv;
	xmlClientInfo(XmlConfig config) : IConfigOpeation(config), HandlerCount(5000), MaxHandlerCount(10000), MaxConnectTime(120),
		CheckAliveTime(60), MaxBuffRecv(1024) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlModuleInfos : public IConfigOpeation
{
public:
	class _ModuleInfo
	{
	public:
		std::string szModuleName;
		std::string szModulePath;
		std::string szModuleParam;
		_ModuleInfo() : szModuleName("TcpTest.dll"), szModulePath("./"), szModuleParam("") {}
	};
	std::vector<_ModuleInfo> vec;
	xmlModuleInfos(XmlConfig config) : IConfigOpeation(config) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlModuleMangager : public IConfigOpeation
{
public:
	uint32 MaxCount;
	xmlModuleMangager(XmlConfig config) : IConfigOpeation(config), MaxCount(100) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};
class xmlMonitor : public IConfigOpeation
{
public:
	uint8 CpuAndMemory;
	uint16 CpuMax;
	uint32 MemoryMax;
	xmlMonitor(XmlConfig config) : IConfigOpeation(config), CpuAndMemory(1), CpuMax(50), MemoryMax(1000) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlThreadInfoAI : public IConfigOpeation
{
public:
	uint8 AI;
	uint8 ReturnDataType;
	uint16 CheckTime;
	uint16 TimeoutCount;
	uint16 StopTime;
	std::string ReturnData;
	xmlThreadInfoAI(XmlConfig config) : IConfigOpeation(config), AI(0), ReturnDataType(1), CheckTime(30),
		TimeoutCount(1), StopTime(30), ReturnData("ff ff") {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlThreadInfo : public IConfigOpeation
{
public:
	uint16 ThreadTimeout;
	uint16 ThreadTimeCheck;
	uint16 DisposeTimeout;
	uint16 PutQueueTimeout;
	xmlThreadInfo(XmlConfig config) : IConfigOpeation(config), ThreadTimeout(30), ThreadTimeCheck(60),
		DisposeTimeout(40), PutQueueTimeout(100) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlConsole : public IConfigOpeation
{
public:
	uint8 support;
	std::string sip;
	uint16 sport;
	xmlConsole(XmlConfig config) : IConfigOpeation(config), support(1), sip("INADDR_ANY"), sport(10010) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlConsoleKeys : public IConfigOpeation
{
public:
	class _ConsoleKey
	{
	public:
		std::string Key;
		_ConsoleKey() : Key("not") {}
	};
	std::vector<_ConsoleKey> vec;
	xmlConsoleKeys(XmlConfig config) : IConfigOpeation(config) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlAceDebug : public IConfigOpeation
{
public:
	uint8 TrunOn;
	std::string DebugName;
	uint16 ChkInterval;
	uint32 LogFileMaxSize;
	uint8 LogFileMaxCnt;
	std::string Level;
	xmlAceDebug(XmlConfig config) : IConfigOpeation(config), TrunOn(0), DebugName("./serverdebug.log"), ChkInterval(600),
		LogFileMaxSize(10240), LogFileMaxCnt(3), Level("") {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlCommandAccount : public IConfigOpeation
{
public:
	uint8 Account;
	uint8 FlowAccount;
	uint32 MaxCommandCount;
	xmlCommandAccount(XmlConfig config) : IConfigOpeation(config), Account(1), FlowAccount(1), MaxCommandCount(2000) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlCoreSetting : public IConfigOpeation
{
public:
	uint8 CoreNeed;
	std::string Script;
	xmlCoreSetting(XmlConfig config) : IConfigOpeation(config), CoreNeed(0), Script("") {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlServerType : public IConfigOpeation
{
public:
	uint8 Type;
	std::string name;
	std::string displayname;
	uint8 Debug;
	uint32 DebugSize;
	uint8 IsClose;
	xmlServerType(XmlConfig config) : IConfigOpeation(config), Type(0), name("Pss Service"),
		displayname("PssService"), Debug(0), DebugSize(1000), IsClose(0) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlServerID : public IConfigOpeation
{
public:
	uint32 id;
	xmlServerID(XmlConfig config) : IConfigOpeation(config), id(1001) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlServerName : public IConfigOpeation
{
public:
	std::string name;
	xmlServerName(XmlConfig config) : IConfigOpeation(config), name("Freeeyes") {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlServerVersion : public IConfigOpeation
{
public:
	std::string Version;
	xmlServerVersion(XmlConfig config) : IConfigOpeation(config), Version("1.00") {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlPacketParses : public IConfigOpeation
{
public:
	class _PacketParse
	{
	public:
		uint16 uParseID;
		std::string szModulePath;
		std::string szModuleName;
		std::string szType;
		uint16 uOrgLength;
		_PacketParse() : uParseID(1), szModulePath("./"),
			szModuleName("PacketParse_Interface.dll"), szType("STREAM"), uOrgLength(40) {}
	};
	std::vector<_PacketParse> _vec;
	xmlPacketParses(XmlConfig config) : IConfigOpeation(config) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlBuffPacket : public IConfigOpeation
{
public:
	uint32 Count;
	xmlBuffPacket(XmlConfig config) : IConfigOpeation(config), Count(5000) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlMessage : public IConfigOpeation
{
public:
	uint32 Msg_High_mark;
	uint32 Msg_Low_mark;
	uint32 Msg_Buff_Max_Size;
	uint16 Msg_Thread;
	uint32 Msg_MaxQueue;
	xmlMessage(XmlConfig config) : IConfigOpeation(config), Msg_High_mark(64000), Msg_Low_mark(64000), Msg_Buff_Max_Size(20480),
		Msg_Thread(5), Msg_MaxQueue(10000) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};



/****************************alert.xml*****************************/
class xmlAlertConnect : public IConfigOpeation
{
public:
	uint8 ConnectMin;
	uint32 ConnectMax;
	uint16 DisConnectMin;
	uint32 DisConnectMax;
	uint32 ConnectAlert;
	uint32 MailID;
	xmlAlertConnect(XmlConfig config) : IConfigOpeation(config), ConnectMin(0), ConnectMax(0), DisConnectMin(0),
		DisConnectMax(0), ConnectAlert(20000), MailID(0) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlIP : public IConfigOpeation
{
public:
	uint8 IPMax;
	uint32 Timeout;
	xmlIP(XmlConfig config) : IConfigOpeation(config), IPMax(0), Timeout(300) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlClientData : public IConfigOpeation
{
public:
	uint16 RecvPacketCount;
	uint32 RecvDataMax;
	uint16 SendPacketCount;
	uint32 SendDataMax;
	uint32 MailID;
	xmlClientData(XmlConfig config) : IConfigOpeation(config), RecvPacketCount(0), RecvDataMax(0), SendPacketCount(0),
		SendDataMax(0), MailID(0) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlCommandInfo : public IConfigOpeation
{
public:
	uint32 CommandID;
	uint32 CommandCount;
	uint32 MailID;
	xmlCommandInfo(XmlConfig config) : IConfigOpeation(config), CommandID(4096), CommandCount(0), MailID(0) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlMail : public IConfigOpeation
{
public:
	uint16 MailID;
	std::string fromMailAddr;
	std::string toMailAddr;
	uint32 MailPass;
	std::string MailUrl;
	uint16 MailPort;
	xmlMail(XmlConfig config) : IConfigOpeation(config), MailID(1), fromMailAddr("local@163.com"), toMailAddr("freeeyes@163.com"),
		MailPass(123456), MailUrl("smtp.163.com"), MailPort(25) {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlWorkThreadChart : public IConfigOpeation
{
public:
	uint16 JsonOutput;
	uint32 Count;
	std::string File;
	xmlWorkThreadChart(XmlConfig config) : IConfigOpeation(config), JsonOutput(1), Count(10),
		File("./Log/WorkThread.json") {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlConnectChart : public IConfigOpeation
{
public:
	uint16 JsonOutput;
	uint32 Count;
	std::string File;
	xmlConnectChart(XmlConfig config) : IConfigOpeation(config), JsonOutput(1), Count(10),
		File("./Log/ConnnectInfo.json") {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

class xmlCommandChart : public IConfigOpeation
{
public:
	uint16 JsonOutput;
	uint32 Count;
	uint32 CommandID;
	std::string File;
	xmlCommandChart(XmlConfig config) : IConfigOpeation(config), JsonOutput(1), Count(10), CommandID(4096),
		File("./Log/Command4096.json") {}
	bool Init(CXmlOpeation* pXmlOpeation);
};

