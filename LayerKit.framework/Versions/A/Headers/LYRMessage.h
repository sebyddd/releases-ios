//
//  LYRMessage.h
//  LayerKit
//
//  Created by Blake Watters on 5/8/14.
//  Copyright (c) 2014 Layer Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@class LYRConversation;

/**
 @abstract `LYRRecipientStatus` is an enumerated value that describes the status of a given Message for a specific participant in the Conversation to which the Message belongs.
 */
typedef NS_ENUM(NSInteger, LYRRecipientStatus) {
    /// @abstract Status for the recipient cannot be determined because the message is not in a state in which recipient status can be evaluated or the user is not a participant in the Conversation.
    LYRRecipientStatusInvalid   = -1,
    
    /// @abstract The message has been transported to Layer and is awaiting synchronization by the recipient's devices.
	LYRRecipientStatusSent      = 0,
	
    /// @abstract The message has been synchronized to at least one device for a recipient but has not been marked as read.
	LYRRecipientStatusDelivered = 1,
	
    /// @abstract The message has been marked as read by one of the recipient's devices.
	LYRRecipientStatusRead      = 2
};

/**
 @abstract The `LYRMessage` class represents a message within a conversation (modeled by the `LYRConversation` class) between two or
 more participants within Layer.
 */
@interface LYRMessage : NSObject

/**
 @abstract A unique identifier for the message.
 */
@property (nonatomic, readonly) NSURL *identifier;

/**
 @abstract Object index dictating message order in a conversation.
 
 @discussion Unsent messages have index value of `NSNotFound`.
 */
@property (nonatomic, readonly) NSUInteger index;

/**
 @abstract The conversation that the receiver is a part of.
 */
@property (nonatomic, readonly) LYRConversation *conversation;

/**
 @abstract An array of message parts (modeled by the `LYRMessagePart` class) that provide access to the content of the receiver.
 */
@property (nonatomic, readonly) NSArray *parts;

/**
 @abstract Returns a Boolean value that indicates if the receiver is a draft.
 
 @discussion Draft messages are persisted into the local database but will not be transported to Layer until the client is instructed to send the message.
 */
@property (nonatomic, readonly) BOOL isDraft;

/**
 @abstract Returns a Boolean value that is true when the receiver has been sent by a client, but not yet transported to Layer.
 
 @discussion A message becomes pending once it is sent via a client and remains pending until successfully posted to Layer for synchronization by recipients. 
 For a connnected client, messages will remain pending only until the next synchronization operation is completed. For offline clients the message will remain pending
 until network access becomes available and synchronization can be performed.
 */
@property (nonatomic, readonly) BOOL isPending;

/**
 @abstract Returns a Boolean value that indicates if the receiver has been deleted.
 */
@property (nonatomic, readonly) BOOL isDeleted;

/**
 @abstract A dictionary of metadata about the message synchronized among all participants.
 
 @discussion The metadata is a free-form structure for embedding synchronized data about the conversation that is
 to be shared among the participants. For example, a message might be designated as important by embedding a Boolean value
 within the metadata dictionary.
 */
@property (nonatomic, readonly) NSDictionary *metadata;

/**
 @abstract A dictionary of private, user-specific information about the message.
 
 @discussion The user info is a free-form structure for embedding data about the conversation that is synchronized between all the devices
 of the authenticated user, but is not shared with any other participants. For example, an applicatication may wish to flag a message for
 future follow-up by the user by embedding a Boolean value into the user info dictionary.
 */
@property (nonatomic, readonly) NSDictionary *userInfo;

/**
 @abstract The date and time that the message was originally sent.
 */
@property (nonatomic, readonly) NSDate *sentAt;

/**
 @abstract The date and time that the message was received by the authenticated user or `nil` if the current user sent the message.
 */
@property (nonatomic, readonly) NSDate *receivedAt;

/**
 @abstract The user ID of the user who sent the message.
 */
@property (nonatomic, readonly) NSString *sentByUserID;

///------------------------------
/// @name Accessing Read Receipts
///------------------------------

/**
 @abstract Returns a dictionary keyed the user ID of all participants in the Conversation that the receiver belongs to and whose
 values are an `NSNumber` representation of the receipient status (`LYRRecipientStatus` value) for their corresponding key.
 */
@property (nonatomic, readonly) NSDictionary *recipientStatusByUserID;

/**
 @abstract Retrieves the message state for a given participant in the conversation.
 
 @param userID The user ID to retrieve the message status for.
 @return An `LYRRecipientStatus` value specifying the message status for the given participant or `LYRRecipientStatusInvalid` if the specified user is not a participant in the conversation.
 */
- (LYRRecipientStatus)recipientStatusForUserID:(NSString *)userID;

@end
