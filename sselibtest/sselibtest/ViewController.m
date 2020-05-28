//
//  ViewController.m
//  sselibtest
//
//  Created by marklei on 2020/4/10.
//  Copyright © 2020 swaiot. All rights reserved.
//

#import "ViewController.h"
#import <SSELib/SSEEnum.h>
@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

/**
 调用了[[SSEManager sharedInstance]syncFileToCloud:]发发之后的异步回调
 发送文件到bos存储服务，发送过程是异步的，发送成功/失败都会回调到函数。
 @param sendResule 文件上传结果
 SENDFILE_ERROR = -1, //发送失败了
 SENDFILE_ONPROGRESS = 0, //发送的进度回调
 SENDFILE_FINISHED=1,//发送完成了
 @param fileKey 文件上传标识
 */
-(void) onSendFileToCloud:(SendFileResult)sendResule fileKey:(NSString*)fileKey destDId:(NSString*) destDId progress:(NSNumber*)progress error:(NSError*)err{
    NSLog(@"onSendFileToCloud errorCode: %ld filekey: %@", sendResule, fileKey);

}

/**
 调用了[[SSEManager sharedInstance]syncFileFromCloud:]之后的异步回调
 从bos存储服务下载文件的过程，下载过程是异步的，接收成功/失败都会回调到函数。
 @param receivedResult 文件下载结果
 RECEIVEFILE_ERROR = -1, //下载文件失败了
 RECEIVEFILE_ONPROGRESS = 0, //下载文件的进度回调
 SENDFILE_FINISHED=1,//下载文件完成了
 @param fileKey 文件在bos上的唯一标识
 @param savedUrl 文件下载到本地的路径地址
 @param err 文件下载错误信息
 */
-(void) onReceivedFileFromCloud:(ReceivedFileResult)receivedResult fileKey:(NSString*)fileKey savedPath:(NSString*)savedUrl progress:(NSNumber*)progress error:(NSError*)err{
    NSLog(@"onSendFileToCloud errorCode: %ld filekey: %@ savedpath: %@ progress: %ld err=%@ ", receivedResult, fileKey,savedUrl,[progress integerValue],[err description]);

}

/**
 FIXME:
      从swaiot开放平台获得的APPEKY和APPSALT，其中APPKEY填到info.plist当中增加：SSEAPPKEY并填入值
            此处填入APPSALT
 */
-(NSString*) saltOfSSETunnel{
    return @"";
}

/**
 SSELib库的错误回调
 @param errorCode 错误code
 ConnectHostFail =0,  //连不上服务器错误
 SSEDisconnect =1,  //服务器断开连接错误
 SSESendError = 2, //发送失败错误
 ConnectBosHostFail = 3, //获取bos地址错误
 @param errMsg 库错误消息
 
 */
-(void) onSSEError:(SSEConnectError)errorCode errString:(NSString*) errMsg {
    NSLog(@"onSSEError errorCode: %ld errString: %@", errorCode, errMsg);
}

/**
 SSE连接成功之后的回调
 */
-(void) onSSETunnelStarted {
    NSLog(@"onSSETunnelStarted");
}

/**
 接收到其他设备、或者其他服务器推送过来的消息
 @param msgId  唯一设备消息id
 @param eventName 消息名称
 @param message 消息数据
 */
-(void) onReceiveSSEMessage:(NSString*)msgId msgName:(NSString*) eventName msg:(NSString*)message {
    NSLog(@"onReceiveSSEMessage msgId: %@ eventName: %@ message: %@", msgId, eventName, message);
}

/**
 调用[[SSEManager sharedInstance] sendMessage]结果的回调
 @param resultCode 发送结果
 TARGETOFFLINEERROR = 0,  //发送失败，发生了错误
 TARGETONLINESUCCESS =1,
 @param dest 发送到的目标id
 @param messageId 发送的消息序列号id
 @param eventName 发送的消息名称
 @param message 发送的消息内容
 */
-(void) onSendSSEResult:(SSESendResult) resultCode destStr:(NSString*)dest msgId:(NSString*)messageId msgName:(NSString*) eventName msg:(NSString*)message{
    NSLog(@"onSendSSEResult resultCode: %ld dest: %@ messageId: %@ eventName: %@ message: %@", resultCode, dest, messageId, eventName, message);
}

- (IBAction)do_connect:(id)sender {
    [SSEManager sharedInstance].delegate = self;
       [[SSEManager sharedInstance] connect_sse:@"unique_device_id" uid:@""];
}
- (IBAction)do_send:(id)sender {
    if ([[SSEManager sharedInstance] isSSEStarted]) {
           [[SSEManager sharedInstance] sendMessage : @"unique_device_id" msgId:@"uniquemessageid" msgName:@"msgName" msg:@"helloworld"];
       }
}
- (IBAction)do_reconnect:(id)sender {
    [[SSEManager sharedInstance] reConnect_sse:@"unique_device_id" uid:@""];
}
- (IBAction)do_sendfile:(id)sender {
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *imgfile = [bundle pathForResource:@"22" ofType:@"jpg"];
    [[SSEManager sharedInstance]syncFileToCloud:@"unique_device_id" file:imgfile uid:@"unique_device_id"];
}

@end
