#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"

class HttpClientTest : public cocos2d::Layer
{
public:
    HttpClientTest();
    virtual ~HttpClientTest();
    void toExtensionsMainLayer(cocos2d::Ref *sender);
    
    //Menu Callbacks
    void onMenuGetTestClicked(cocos2d::Ref *sender);
    void onMenuPostTestClicked(cocos2d::Ref *sender);
    void onMenuPostBinaryTestClicked(cocos2d::Ref *sender);
    void onMenuPutTestClicked(cocos2d::Ref *sender);
    void onMenuDeleteTestClicked(cocos2d::Ref *sender);
    
    //Http Response Callback
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);

private:
    cocos2d::LabelTTF* _labelStatusCode;
};

void runHttpClientTest();

#endif //__HTTPREQUESTHTTP_H
