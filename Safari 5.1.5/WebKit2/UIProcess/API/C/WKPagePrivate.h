/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WKPagePrivate_h
#define WKPagePrivate_h

#include <WebKit2/WKBase.h>
#include <WebKit2/WKPage.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*WKPageRenderTreeExternalRepresentationFunction)(WKStringRef, WKErrorRef, void*);
WK_EXPORT void WKPageRenderTreeExternalRepresentation(WKPageRef page, void *context, WKPageRenderTreeExternalRepresentationFunction function);

#ifdef __BLOCKS__
typedef void (^WKPageRenderTreeExternalRepresentationBlock)(WKStringRef, WKErrorRef);
WK_EXPORT void WKPageRenderTreeExternalRepresentation_b(WKPageRef page, WKPageRenderTreeExternalRepresentationBlock block);
#endif

enum {
    kWKDebugFlashViewUpdates = 1 << 0,
    kWKDebugFlashBackingStoreUpdates = 1 << 1
};
typedef unsigned WKPageDebugPaintFlags;

WK_EXPORT void WKPageSetDebugPaintFlags(WKPageDebugPaintFlags flags);
WK_EXPORT WKPageDebugPaintFlags WKPageGetDebugPaintFlags(void);

struct WKPrintInfo {
    float pageSetupScaleFactor;
    float availablePaperWidth;
    float availablePaperHeight;
};
typedef struct WKPrintInfo WKPrintInfo;

typedef void (*WKPageComputePagesForPrintingFunction)(WKRect* pageRects, uint32_t pageCount, double resultPageScaleFactor, WKErrorRef error, void* functionContext);
WK_EXPORT void WKPageComputePagesForPrinting(WKPageRef page, WKFrameRef frame, WKPrintInfo, WKPageComputePagesForPrintingFunction, void* context);

typedef void (*WKPageDrawToPDFFunction)(WKDataRef data, WKErrorRef error, void* functionContext);
WK_EXPORT void WKPageBeginPrinting(WKPageRef page, WKFrameRef frame, WKPrintInfo printInfo);
WK_EXPORT void WKPageDrawPagesToPDF(WKPageRef page, WKFrameRef frame, WKPrintInfo printInfo, uint32_t first, uint32_t count, WKPageDrawToPDFFunction callback, void* context);

// FIXME: This is in violation of the no synchronous messages to the Web Process policy and should
// be removed as soon as possible.
WK_EXPORT WKImageRef WKPageCreateSnapshotOfVisibleContent(WKPageRef page);

#ifdef __cplusplus
}
#endif

#endif /* WKPagePrivate_h */
