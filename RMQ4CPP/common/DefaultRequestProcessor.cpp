/******************************************************************************************
* RMQ4CPP 
* Auther : luxiang
* github:https://github.com/Lxxing?tab=repositories
* ��ӭ����ָ�� xiaoxiaomiantianwo@163.com
******************************************************************************************/
#include "DefaultRequestProcessor.h"
#include "RemotingCommand.h"
#include "MQProtos.h"
#include "MQVersion.h"
#include "RegisterBrokerRequestHeader.h"
#include "GetRouteInfoRequestHeader.h"

#include "NamesrvController.h"

namespace lxmq{

DefaultRequestProcessor::DefaultRequestProcessor(NamesrvController *rs)
{
	this->namesrvController = rs;
}

DefaultRequestProcessor::~DefaultRequestProcessor()
{

}

RemotingCommand DefaultRequestProcessor::processRequest(const MQBuffer & msg)
{
	RemotingCommand* request = nullptr;
  	try {
    	request = RemotingCommand::Decode(msg);
  	} catch (...) {
    	printf("processData error");
    	return *request;
  	}
  	
    int code = request->getCode();
	
	switch (code) {
		case PUT_KV_CONFIG:
			//return this.putKVConfig(ctx, request);
			break;
		case GET_KV_CONFIG:
			//return this.getKVConfig(ctx, request);
			break;
		case DELETE_KV_CONFIG:
			//return this.deleteKVConfig(ctx, request);
			break;
		case QUERY_DATA_VERSION:
			//return queryBrokerTopicConfig(ctx, request);
			break;
		case REGISTER_BROKER:
		{
			MQVersion::Version brokerVersion = MQVersion::value2Version(request->getVersion());
			if (brokerVersion >= MQVersion::Version::V3_0_11)
			{
				return this->registerBrokerWithFilterServer(request);
			}
			else
			{
				return this->registerBroker(request);
			}
			break;
		}
		case UNREGISTER_BROKER:
			//return this.unregisterBroker(ctx, request);
			break;
		case GET_ROUTEINTO_BY_TOPIC:
			return this->getRouteInfoByTopic(request);
			break;
		case GET_BROKER_CLUSTER_INFO:
			//return this.getBrokerClusterInfo(ctx, request);
			break;
		case WIPE_WRITE_PERM_OF_BROKER:
			//return this.wipeWritePermOfBroker(ctx, request);
			break;
		case GET_ALL_TOPIC_LIST_FROM_NAMESERVER:
			//return getAllTopicListFromNameserver(ctx, request);
			break;
		case DELETE_TOPIC_IN_NAMESRV:
			//return deleteTopicInNamesrv(ctx, request);
			break;
		case GET_KVLIST_BY_NAMESPACE:
			//return this.getKVListByNamespace(ctx, request);
			break;
		case GET_TOPICS_BY_CLUSTER:
			//return this.getTopicsByCluster(ctx, request);
			break;
		case GET_SYSTEM_TOPIC_LIST_FROM_NS:
			//return this.getSystemTopicListFromNs(ctx, request);
			break;
		case GET_UNIT_TOPIC_LIST:
			//return this.getUnitTopicList(ctx, request);
			break;
		case GET_HAS_UNIT_SUB_TOPIC_LIST:
			//return this.getHasUnitSubTopicList(ctx, request);
			break;
		case GET_HAS_UNIT_SUB_UNUNIT_TOPIC_LIST:
			//return this.getHasUnitSubUnUnitTopicList(ctx, request);
			break;
		case UPDATE_NAMESRV_CONFIG:
			//return this.updateConfig(ctx, request);
			break;
		case GET_NAMESRV_CONFIG:
			//return this.getConfig(ctx, request);
			break;
		default:
			break;
	}

  return *request;
}


RemotingCommand DefaultRequestProcessor::registerBroker( RemotingCommand *request) 
{
    RemotingCommand response;
	Json::Value& pj = request->getParsedJson();
	Json::Value ext = pj["extFields"];
	RegisterBrokerRequestHeader *requestHeader = 
		(RegisterBrokerRequestHeader*)RegisterBrokerRequestHeader::decodeCommandCustomHeader(ext);
	

    this->namesrvController->getRouteInfoManager()->registerBroker(
    	requestHeader->getClusterName(),
        requestHeader->getBrokerAddr(),
        requestHeader->getBrokerName(),
        requestHeader->getBrokerId(),
        requestHeader->getHaServerAddr()
     );

     
     return response;
}

RemotingCommand DefaultRequestProcessor::registerBrokerWithFilterServer( RemotingCommand *request) 
{
	//request->SetExtHeader(request->getCode());

	RemotingCommand response;

	Json::Value& pj = request->getParsedJson();
	Json::Value ext = pj["extFields"];
	RegisterBrokerRequestHeader *requestHeader = 
		(RegisterBrokerRequestHeader*)RegisterBrokerRequestHeader::decodeCommandCustomHeader(ext);
	
	this->namesrvController->getRouteInfoManager()->registerBroker(
		requestHeader->getClusterName(),
		requestHeader->getBrokerAddr(),
		requestHeader->getBrokerName(),
		requestHeader->getBrokerId(),
		requestHeader->getHaServerAddr()
		);
	
		 
	return response;
}

RemotingCommand DefaultRequestProcessor::getRouteInfoByTopic(RemotingCommand *request)
{
	RemotingCommand response;

	Json::Value& pj = request->getParsedJson();
	Json::Value ext = pj["extFields"];
	GetRouteInfoRequestHeader *requestHeader = 
		(GetRouteInfoRequestHeader*)GetRouteInfoRequestHeader::decodeCommandCustomHeader(ext);
	
	this->namesrvController->getRouteInfoManager()->pickupTopicRouteData(
		requestHeader->getTopic()
		);
	
		 
	return response;

}

    

}//    end of lxmq

