// Copyright (C) 2016 Caitlin Potter & Contributors. All rights reserved.
// Use of this source is governed by the Apache License, Version 2.0 that
// can be found in the LICENSE file, which must be distributed with this
// software.

#pragma once

#ifdef TSW_WEBVIEW_WKWEBVIEW

#include <twitchsw/twitchsw.h>
#include <twitchsw/webview.h>

#include <string>

#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#import <WebKit/WebKit.h>

#import "mac/WebViewController.h"

#if !__has_feature(objc_arc)
#error "ARC has not been enabled"
#endif

namespace twitchsw {

class WebViewImpl {
public:
    WebViewImpl();
    ~WebViewImpl();

    static void initialize();
    static void shutdown();

    void open(const std::string& url, const HttpRequestOptions& options);
    void close();
    void setTitle(const std::string& title);
    void show();

    void setOnRedirect(const OnRedirectCallback& callback);
    void setOnComplete(const OnCompleteCallback& callback);
    void setOnAbort(const OnAbortCallback& callback);

    void* nativeHandle();

    // Helpers for WebViewController
    const OnRedirectCallback& onRedirect() const { return m_onRedirect; }
    const OnCompleteCallback& onComplete() const { return m_onComplete; }
    const OnAbortCallback& onAbort() const { return m_onAbort; }

    void didClose();
    inline Ref<WebView> webView() { return Ref<WebView>(*m_webView.get()); }
    inline bool hasWebView() const { return !m_webView.isNull(); }

protected:
    bool ensureUI();

private:
    friend class WebView;
    RefPtr<WebView> m_webView; // Keep holder alive until WebViewImpl is destroyed
    WebViewController* m_controller;
    NSWindow* m_window;
    NSWindowController* m_windowController;
    OnRedirectCallback m_onRedirect;
    OnCompleteCallback m_onComplete;
    OnAbortCallback m_onAbort;

    std::string m_title;
};

}  // namespace twitchsw

#endif  // TSW_WEBVIEW_WKWEBVIEW
