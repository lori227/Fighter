#ifndef __KF_HTTP_DATA_H__
#define __KF_HTTP_DATA_H__

#include "KFrame.h"

namespace KFrame
{
    class KFHttp;
    class KFHttpData
    {
    public:
        KFHttpData();
        ~KFHttpData();

        // ִ���߼�
        void Request();

        // ���ʽ���
        void Response();
    public:
        // ���ʵ�ַ
        std::string _url;

        // ��������
        uint32 _type;

        // ��������
        std::string _data;

        // �ش�����
        std::string _args;

        // ��������
        std::string _result;

        // �ص�����
        KFHttpClientFunction _function;

        // httpclient
        KFHttp* _http;
    };
}


#endif