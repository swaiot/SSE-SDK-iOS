#### Swaiot开放平台下推送SDK库

##### iOS-SDK及demo下载地址
https://github.com/swaiot/SSE-SDK-iOS

##### 安装方式
- 1 在开放平台上获得分配到的Swaiot开发者appkey和saltkey;
- 2 在工程的Frameworks目录中拖入SSELib.framework（合并了真机和虚拟机的framework） ;
- 3 在工程配置的Build Settings 分支下的Other Linker Flags当中增加如下:
~~~ objc
   -lObjC
   -lc++
~~~
- 4 在工程共层代码的Info.plist中增加键值对:
~~~ objc
key: SSEAPPKEY  value: swaiot开放平台分配到的APPKEY
~~~

- 5 实现<SSELibDelegate>的委托监听,在监听代码中的实现接口中填如saltkey．
~~~ objc
/**
 FIXME:
      从swaiot开放平台获得的APPEKY和APPSALT，其中APPKEY填到info.plist当中增加：SSEAPPKEY并填入值
            此处填入APPSALT
 */
-(NSString*) appSalt {
    return @"";
}
~~~

详细可见下载地址中的sselibtest工程的配置及代码说明.

##### API说明

###### SSEManager 类API
~~~ objc
/**
 单例
 */
+ (instancetype)sharedInstance;
~~~

~~~ objc
/*
   * 连接SSE平台
     * @param did 链接到IOTSSE平台的did 必须唯一，本机唯一did
     * @param uid 链接到IOTSSE平台的uid，swaiot平台用户唯一uid,可以为空
     * @return ture 成功,false 失败
 */
-(bool) connect_sse:(NSString*)did uid:(NSString*)uid ;
~~~

~~~ objc
/**
     * 重新连接SSE平台
     * 在设备上的uid发生变化的时候，请调用该方法
     * @param did　必传，用于唯一标识设备消息接收，全网唯一ID
     * @param uid　可以为空，如果不为空，则发送方发送的消息给设备需要did&uid的完整组合才能确保接收到消息
     * @return true:重连正常 false：重连不正常
 */
-(bool) reConnect_sse:(NSString*)did uid:(NSString*)uid ;
~~~

~~~ objc
/**
     * 发送消息给其他设备
     * @param destDid 发送到的设备ｉd
     * @param mid 发送的消息ｉｄ
     * @param msgName　发送的消息名称
     * @param msg　发送的消息
     * @return true 成功加入发送队列，false 加入发送队列失败
     */
-(bool) sendMessage:(NSString*)destDid msgId:(NSString*)mid msgName:(NSString*)msgName msg:(NSString*)msg;
~~~

~~~ ojbc
/**
     * 该接口为异步接口，可以同时发给多个设备不同的文件。
     * 发送过程由onSendFileToCloud 进行回调
     * @param destDid 发送文件给到的目标设备id
     * @param filePath 要发送的文件的本地路径地址
     * @param uid，用来标识文件上传方的id，建议传入connectSSE方法的did参数．
     */
-(void) syncFileToCloud:(NSString*)destDid file:(NSString*)filePath uid:(NSString*)uid;
~~~

~~~ objc
/**
     * 从云端同步文件，该接口为异步接口，可同时同步多个文件
     * @param fileKey onSendFileToCloud 完成时候，回调的fileKey
	 * 该fileKey是发送方调用syncFileToCloud之后接受到的消息，然后发送方再调用sendMessage接口将fileKey传递给消息接收方，接收方完成文件下载．会将文件存储于应用纱盒的cache目录
     */
-(void) syncFileFromCloud:(NSString*)fileKey;
~~~

~~~ objc
/**
     * @return true SSE已经连接成功,false 失败
     */
-(bool) isSSEStarted;
~~~

###### @protocol SSELibDelegate <NSObject>回调API

~~~ objc
/**
 调用了[[SSEManager sharedInstance]syncFileToCloud:]发发之后的异步回调
 发送文件到bos存储服务，发送过程是异步的，发送成功/失败都会回调到函数。
 @param sendResult 文件上传结果
 SENDFILE_ERROR = -1, //发送失败了
 SENDFILE_ONPROGRESS = 0, //发送的进度回调
 SENDFILE_FINISHED=1,//发送完成了
 @param fileKey 文件上传标识
 */
-(void) onSendFileToCloud:(SendFileResultEnum)sendResult fileKey:(NSString*)fileKey destDId:(NSString*) destDId progress:(NSNumber*)progress error:(NSError*)err;
~~~

~~~ objc
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
-(void) onReceivedFileFromCloud:(ReceivedFileResultEnum)receivedResult fileKey:(NSString*)fileKey savedPath:(NSString*)savedUrl progress:(NSNumber*)progress error:(NSError*)err;
~~~

~~~ objc
/**
 FIXME:
      从swaiot开放平台获得的APPEKY和APPSALT，其中APPKEY填到info.plist当中增加：SSEAPPKEY并填入值
            此处填入APPSALT
 */
-(NSString*) appSalt ;
~~~

~~~ objc
/**
 SSELib库的错误回调
 @param errorCode 错误code
 ConnectHostFail =0,  //连不上服务器错误
 SSEDisconnect =1,  //服务器断开连接错误
 SSESendError = 2, //发送失败错误
 ConnectBosHostFail = 3, //获取bos地址错误
 @param errMsg 库错误消息
 */
-(void) onSSEError:(SSEErrorEnum)errorCode errString:(NSString*) errMsg ;
~~~

~~~ objc
/**
 SSE连接成功之后的回调
 */
-(void) onSSETunnelStarted ;
~~~

~~~ objc
/**
 接收到其他设备、或者其他服务器推送过来的消息
 @param msgId  唯一设备消息id
 @param eventName 消息名称
 @param message 消息数据
 */
-(void) onReceiveSSEMessage:(NSString*)msgId msgName:(NSString*) eventName msg:(NSString*)message ;
~~~

~~~ objc
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
-(void) onSendSSEResult:(SSESendResultEnum) resultCode destStr:(NSString*)dest msgId:(NSString*)messageId msgName:(NSString*) eventName msg:(NSString*)message;
~~~
