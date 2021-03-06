//
//  SPEvent.h
//  Sparrow
//
//  Created by Daniel Sperl on 27.04.09.
//  Copyright 2011-2015 Gamua. All rights reserved.
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the Simplified BSD License.
//

#import <Sparrow/SparrowBase.h>
#import <Sparrow/SPMacros.h>

NS_ASSUME_NONNULL_BEGIN

SP_EXTERN NSString *const SPEventTypeAdded;
SP_EXTERN NSString *const SPEventTypeAddedToStage;
SP_EXTERN NSString *const SPEventTypeRemoved;
SP_EXTERN NSString *const SPEventTypeRemovedFromStage;
SP_EXTERN NSString *const SPEventTypeRemoveFromJuggler;
SP_EXTERN NSString *const SPEventTypeCompleted;
SP_EXTERN NSString *const SPEventTypeTriggered;
SP_EXTERN NSString *const SPEventTypeFlatten;
SP_EXTERN NSString *const SPEventTypeRender;
SP_EXTERN NSString *const SPEventTypePress;

@class SPEventDispatcher;

/** ------------------------------------------------------------------------------------------------

 The SPEvent class contains data that describes an event.
 
 `SPEventDispatcher`s create instances of this class and send them to registered listeners. An event
 contains information that characterizes an event, most importantly the event type and if the event 
 bubbles. The target of an event is the object that dispatched it.
 
 For some event types, this information is sufficient; other events may need additional information 
 to be carried to the listener. 
 In that case, you can subclass SPEvent and add properties with all the information you require. 
 The SPEnterFrameEvent is an example for this practice; it adds a property about the time that
 has passed since the last frame.
 
 Furthermore, the event class contains methods that can stop the event from being processed by
 other listeners - either completely or at the next bubble stage.
 
------------------------------------------------------------------------------------------------- */

@interface SPEvent : NSObject

/// --------------------
/// @name Initialization
/// --------------------

/// Initializes an event object that can be passed to listeners with a data object. _Designated Initializer_.
- (instancetype)initWithType:(NSString *)type bubbles:(BOOL)bubbles data:(nullable id)object;

/// Initializes an event object that can be passed to listeners.
- (instancetype)initWithType:(NSString *)type bubbles:(BOOL)bubbles;

/// Initializes a non-bubbling event.
- (instancetype)initWithType:(NSString *)type;

/// Factory method.
+ (instancetype)eventWithType:(NSString *)type bubbles:(BOOL)bubbles data:(nullable id)object;

/// Factory method.
+ (instancetype)eventWithType:(NSString *)type bubbles:(BOOL)bubbles;

/// Factory method.
+ (instancetype)eventWithType:(NSString *)type;

/// -------------
/// @name Methods
/// -------------

/// Prevents any other listeners from receiving the event.
- (void)stopImmediatePropagation;

/// Prevents listeners at the next bubble stage from receiving the event.
- (void)stopPropagation;

/// ----------------
/// @name Properties
/// ----------------

/// A string that identifies the event.
@property (nonatomic, readonly) NSString *type; 

/// Indicates if event will bubble.
@property (nonatomic, readonly) BOOL bubbles;

/// Arbitrary data that is attached to the event.
@property (nonatomic, readonly, nullable) id data;

/// The object that dispatched the event.
@property (weak, nonatomic, readonly, nullable) SPEventDispatcher *target;

/// The object the event is currently bubbling at.
@property (weak, nonatomic, readonly, nullable) SPEventDispatcher *currentTarget;

@end

NS_ASSUME_NONNULL_END
