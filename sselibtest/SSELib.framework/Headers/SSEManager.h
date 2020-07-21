//
//  SSEManager.h
//  SSELib
//
//  Created by marklei on 2020/3/9.
//  Copyright © 2020 Skyworth. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SSEEnum.h"
NS_ASSUME_NONNULL_BEGIN

@protocol SSELibDelegate <NSObject>
@required

/// 获取 SSE  Salt
-(NSString*) saltOfSSETunnel;

@optional
/// SSE 通道连接成功
-(void) onSSETunnelStarted;

/// SSE通道连接失败
/// @param errorCode 错误码
/// @param errMsg 错误信息
-(void) onSSEError:(SSEConnectError)errorCode errString:(NSString*) errMsg;


/// 接收到SSE通道的信息
/// @param msgId 消息id
/// @param eventName 消息事件
/// @param message 消息内容
-(void) onReceiveSSEMessage:(NSString*)msgId msgName:(NSString*) eventName msg:(NSString*)message;

/// 发送数据到SSE通道的回调
/// @param resultCode 发送结果的状态
/// @param dest 发送目标
/// @param messageId 消息id
/// @param eventName 事件
/// @param message 内容
-(void) onSendSSEResult:(SSESendResult) resultCode destStr:(NSString*)dest msgId:(NSString*)messageId msgName:(NSString*) eventName msg:(NSString*)message;


/// 发送文件到SSE通道的回调
/// @param sendResule 状态
/// @param fileKey 文件标识
/// @param destDId 目标
/// @param progress 进度
/// @param err 错误
-(void) onSendFileToCloud:(SendFileResult)sendResule fileKey:(NSString*)fileKey destDId:(NSString*) destDId progress:(NSNumber*)progress error:(NSError*)err;


/// 接收文件回调
/// @param receivedResult 状态
/// @param fileKey 文件标识
/// @param savedUrl 保存到本地的缓存路径
/// @param progress 进度
/// @param err 错误
-(void) onReceivedFileFromCloud:(ReceivedFileResult)receivedResult fileKey:(NSString*)fileKey savedPath:(NSString*)savedUrl progress:(NSNumber*)progress error:(NSError*)err;

@end


@interface SSEManager : NSObject

@property(nonatomic, weak) id<SSELibDelegate> delegate;
@property(nonatomic, retain) NSString* autoGenUUID;
/**
 单例
 */
+ (instancetype)sharedInstance;

/**
  SDK自动生成uuid作为唯一标识，接入SSE平台，
  该接口主要用于第三方开放平台下载的APP，uid会保存在本地
 */
-(bool) connect_sse;

/**
   如果是自动生成的UUID，重连逻辑请调用该接口
 */
-(bool) reConnect_sse;

/**
    获得SDK生成的唯一的设备ID
 */
-(NSString*) readUniqueID;

///**
//    注册用户拥有的IOT消息的监听
// */
//-(void) registerListenUserIotMessages:(NSString*)accessToken userID:(NSString*)uid;

///*
// connect_sse 连上iot的sse平台
// 连接SSE，程序初始化完成之后，连入到iot的sse平台
// */
//-(bool) connect_sse:(NSString*)did uid:(NSString*)uid;

/*
 * 连接SSE平台
 * 标准接口，需要根据业务需要传递唯一的ID，为防止冲突，可以增加业务前缀
 * @param did： 业务唯一ID
 * @return true： 成功 false： 失败
 */
-(bool)connect_sse:(NSString*)did;

/**
 *  重连SSE平台，
 *  在设备发生网络状态变化，或者设备唯一ID发生变化的时候，可以调用
 * @param did ：业务接入SSE的唯一ID
 * @return true：成功  false： 失败
 */
-(bool) reConnect_sse:(NSString*)did ;

/*
 * 以智慧屏的方式接入SSE
 * 智慧屏接入方式相比connect_sse接口，云端会增加智慧屏的好友设备列表推送在离线的设备状态消息，以及智慧屏相关业务的其他消息推送
 * 该方法用户智慧屏的相关业务，主要在酷开系统8.x以及有ScreenID关系的设备上，其他第三方请勿使用
 * @param screenID:智慧屏唯一ID
 * @return true：成功 false：失败
 */
-(bool) connect_sse_ASSmartScreen:(NSString*) screenID;

/*
 * 重新连接SSE平台
 * 在设备上，如果网络状态发生变化，或者ScreenID发生了变化，需要重新调用接口
 * @param screenID：智慧屏ID
 * @return true：成功 false：失败
 */
-(bool) reConnect_sse_ASSmartScreen:(NSString*) screenID;

/*
* 以Swaiot-SSE的方式接入SSE
* 该接口相比于connect_sse的接口，云端会增加用户账号下其他IOT设备状态变化的推送
* @param did: 设备作为iot设备的唯一id
* @param accessToken：从酷开账号中心获得的用户授权令牌
* @param useId：从酷开账号中心获得的用户uid
* @return true：成功 false：失败
*/
-(bool) connect_sse_ASIotDevice:(NSString*)did accessToken:(NSString*)userAk userId:(NSString*)uid;

/*
 * 以Swaiot-IOT设备的方式重新接入SSE平台
 * 在设备上，如果网络状态发生变化，或者ScreenID发生了变化，需要重新调用接口
 * @param did:设备唯一id
 * @param accessToken：从酷开账号中心获得的用户授权令牌
 * @param useId：从酷开账号中心获得的用户uid
 * @return true：成功 false：失败
 *
 */
-(bool) reconnect_see_ASIotDevice:(NSString*)did accessToken:(NSString*)userAk userId:(NSString*)uid;
/**
 发送消息给到设备
 */
-(bool) sendMessage:(NSString*)destDid msgId:(NSString*)mid msgName:(NSString*)msgName msg:(NSString*)msg;

/**
 发送文件到云端
 */
-(void) syncFileToCloud:(NSString*)destDid file:(NSString*)filePath uid:(NSString*)uid;

/**
 从云端拉取文件
 */
-(void) syncFileFromCloud:(NSString*)fileKey;

/**
 判断SDK是否启动
 */
-(bool) isSSEStarted;

@end




NS_ASSUME_NONNULL_END

