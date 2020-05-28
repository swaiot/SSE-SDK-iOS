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

/**
 单例
 */
+ (instancetype)sharedInstance;
/*
 connect_sse 连上iot的sse平台
 连接SSE，程序初始化完成之后，连入到iot的sse平台
 */
-(bool) connect_sse:(NSString*)did uid:(NSString*)uid ;

/**
 重连，比如uid切换
 重连会触发SSEDisconnect类型错误回调，不要在这个回调里面继续调用此方法
 */
-(bool) reConnect_sse:(NSString*)did uid:(NSString*)uid ;

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

