//
// Created by consti10 on 20.12.20.
//

#ifndef WIFIBROADCAST_SCHEDULINGHELPER_H
#define WIFIBROADCAST_SCHEDULINGHELPER_H

#include <string>
#include <iostream>
#include <qdebug.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <processthreadsapi.h>
#else
#include <pthread.h>
#include <unistd.h>
#include <sched.h>
#endif

namespace SchedulingHelper {

// this thread should run as close to realtime as possible
#if defined(_WIN32) || defined(_WIN64)
static void setThreadParamsMaxRealtime(HANDLE target) {
    BOOL result = SetThreadPriority(target, THREAD_PRIORITY_TIME_CRITICAL);
    if (!result) {
        qDebug() << "cannot set ThreadParamsMaxRealtime on Windows";
    }
}

static void setThreadParamsMaxRealtime() {
    setThreadParamsMaxRealtime(GetCurrentThread());
}
#else
static void setThreadParamsMaxRealtime(pthread_t target) {
    int policy = SCHED_FIFO;
    sched_param param{};
    param.sched_priority = sched_get_priority_max(policy);
    auto result = pthread_setschedparam(target, policy, &param);
    if (result != 0) {
        qDebug() << "cannot set ThreadParamsMaxRealtime";
    }
}

static void setThreadParamsMaxRealtime() {
    setThreadParamsMaxRealtime(pthread_self());
}
#endif
}
#endif //WIFIBROADCAST_SCHEDULINGHELPER_H
