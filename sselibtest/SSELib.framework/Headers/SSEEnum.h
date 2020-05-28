//
//  SSEEnum.h
//  sselib_iost_test
//
//  Created by zhouzhou on 2020/5/27.
//  Copyright © 2020 Skyworth. All rights reserved.
//

#ifndef SSEEnum_h
#define SSEEnum_h

typedef NS_ENUM(NSInteger, SSEConnectError){
    SSEHostError = 0,//找不到主机
    SSEDisconnectError = 1,//连接断开，已连接时，主动重连的时候会触发，业务层不要调用重新连接的api
    SSEConnectTimeOut = 2,//连接超时，需要重新连接
    SSESendMessageError = 2,//发送数据出现异常
    SSEFileFail = 3,//文件传输出现异常
};

typedef NS_ENUM(NSInteger, SSESendResult){
    SSESendNetworkError = -1,
    SSESendOffLineError = 0,
    SSESendSuccess = 1,
};

typedef NS_ENUM(NSInteger, SendFileResult){
    SendFileError = -1,
    SendFileOnProgress = 0,
    SendFileFinished = 1,
};

typedef NS_ENUM(NSInteger, ReceivedFileResult){
    ReceiveFileError = -1,
    ReceiveFileOnProgress = 0,
    ReceiveFileFinished = 1,
};


#endif /* SSEEnum_h */
