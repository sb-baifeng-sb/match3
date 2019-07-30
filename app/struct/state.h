//
// Created by baifeng on 2019-07-28.
//

#ifndef APP_STATE_H
#define APP_STATE_H

typedef struct {
    char _;
} Indead;  // 死亡中
typedef struct {
    char _;
} Dead;    // 被消除
typedef struct {
    char _;
} Falling; // 下落中
typedef struct {
    char _;
} Linked;

typedef struct {
    char _;
} GemSwapStandby;

typedef struct {
    char _;
} GemSwaping;

typedef struct {
    char _;
} GemReverseSwaping;

typedef struct {
    char _;
} GemSwapFinish;

#endif //APP_STATE_H
