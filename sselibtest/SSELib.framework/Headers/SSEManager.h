//
//  SSEManager.h
//  SSELib
//
//  Created by marklei on 2020/3/9.
//  Copyright © 2020 Skyworth. All rights reserved.
//

#import <Foundation/Foundation.h>
typedef NS_ENUM(NSInteger, SSEErrorEnum){
    ConnectHostFail =0,
   SSEDisconnect =1,
   SSESendError = 2,
   ConnectBosHostFail = 3,
};

typedef NS_ENUM(NSInteger, SSESendResultEnum){
    TARGETOFFLINEERROR = 0,
    TARGETONLINESUCCESS =1,
};

typedef NS_ENUM(NSInteger, SendFileResultEnum){
    SENDFILE_ERROR = -1,
    SENDFILE_ONPROGRESS = 0,
    SENDFILE_FINISHED=1,
};

typedef NS_ENUM(NSInteger, ReceivedFileResultEnum){
    RECEIVEFILE_ERROR=-1,
    RECEIVEFILE_ONPROGRESS = 0,
    RECEIVEFILE_FINISHED=1,
};

NS_ASSUME_NONNULL_BEGIN

@protocol SSELibDelegate <NSObject>
@required//遵守协议必须实现的方法
-(NSString*) appSalt;
-(void) onSSEError:(SSEErrorEnum)errorCode errString:(NSString*) errMsg;
-(void) onSSETunnelStarted;
-(void) onReceiveSSEMessage:(NSString*)msgId msgName:(NSString*) eventName msg:(NSString*)message;
-(void) onSendSSEResult:(SSESendResultEnum) resultCode destStr:(NSString*)dest msgId:(NSString*)messageId msgName:(NSString*) eventName msg:(NSString*)message;
-(void) onSendFileToCloud:(SendFileResultEnum)sendResule fileKey:(NSString*)fileKey destDId:(NSString*) destDId progress:(NSNumber*)progress error:(NSError*)err;
-(void) onReceivedFileFromCloud:(ReceivedFileResultEnum)receivedResult fileKey:(NSString*)fileKey savedPath:(NSString*)savedUrl progress:(NSNumber*)progress error:(NSError*)err;

@optional

@end


@class BGSafeMutableArray;
@interface SSEManager : NSObject
@property(nonatomic, retain) id<SSELibDelegate> delegate;
@property(nonatomic,retain) NSString* DeviceId;
@property(nonatomic,retain) NSString* UserId;
@property(nonatomic,strong) NSThread* connectThread;

@property(strong,nonatomic) BGSafeMutableArray* sendQueue;           //仓库
@property(strong,nonatomic) dispatch_semaphore_t mutex;         //访问仓库（临界区）的互斥访问信号量
@property(strong,nonatomic) dispatch_semaphore_t comsumer_sem;      //生产者-是否生产对象的标记  消费者是否消费仓库对象的标记 使用信
@property(strong,nonatomic) dispatch_semaphore_t product_sem;      //生产者-是否生产对象的标记  消费者是否消费仓库对象的标记 使用信
@property(strong,nonatomic)dispatch_queue_t producerQueue;
@property(strong,nonatomic) dispatch_queue_t consumerQueue;

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

/**
 SSE线程回调
 */
-(void) onSSEError:(NSDictionary*) callBackDic;
-(void) onSSETunnelStarted;
-(void) onReceiveSSEMessage:(NSDictionary*) callBackDic;
-(void) onSendSSEResult:(NSDictionary*) callBackDic;
-(void) onBosTunnelConfiged:(NSDictionary*) callBackDic;
-(void) refreshBosToken;
-(void) onSendFileProgress:(SendFileResultEnum)sendResule fileKey:(NSString*)fileKey destDid:(NSString*) destDid progress:(NSNumber*)progress error:(NSError* _Nullable)err;
-(void) onReceivedFileProgress:(ReceivedFileResultEnum)receivedResult fileKey:(NSString*)fileKey savedPath:(NSString*)savedUrl progress:(NSNumber*)progress error:(NSError* _Nullable)err;

@end



@interface ConnectArgs : NSObject<NSCopying,NSMutableCopying>
@property(nonatomic,retain)NSString *appKey;
@property(nonatomic,retain)NSString *appSalt;
@property(nonatomic,retain)NSString *deviceId;
@property(nonatomic,retain)NSString *userId;
@end

@interface SendArgs : NSObject
@property(nonatomic,retain)NSString *hostAddr;
@property(nonatomic,retain)NSString *destDid;
@property(nonatomic,retain)NSString *msgId;
@property(nonatomic,retain)NSString *msgName;
@property(nonatomic,retain)NSString *msg;
@property(nonatomic,assign)Boolean exitFlag;
@end

NS_ASSUME_NONNULL_END

