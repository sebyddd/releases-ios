# LayerKit Change Log

## 0.19.1

#### Bug Fixes

* Fixed an issue where `synchronizeWithRemoteNotification:completion:` would return an error when invoked when the app is in an inactive state.
* Updated keychain items to allow access when executing in the background.
* LayerKit now uses an alternate global symbol for logging to avoid conflicts with CocoaLumberjack.

## 0.19.0

#### Public API Changes

* Removed all deprecated `LayerKit` methods. 
* Replacing the completion block in `synchronizeWithRemoteNotification:completion` to return the `LYRConversation` and `LYRMessage` objects specified in the remote payload instead of the object changes.
* Introduced `LYRClient` method `waitForCreationOfObjectWithIdentifier:timeout:completion:` that waits the timeout length for creation of the specified identifier's object.

#### Bug Fixes

* Fixes an issue which caused `LYRQueryController` instances to return partially hydrated objects. This could occur when multiple query controllers were attempting to query the same objects from different threads. 

## 0.18.1

#### Bug Fixes

* Fixes an issue that would cause the `LYRQueryController` to broadcast `UPDATE` events with a `newIndexPath` parameter. 
* Fixes an issue that could lead to a crash when syncing conversations that contain blocked participants. 

## 0.18.0

#### Public API Changes 

* Introduced a new deletion mode `LYRDeletionModeMyDevices`, which provides for synchronizing a conversation or message deletion among all of a users devices. 
* Deprecated `LYRDeletionModeLocal` in favor of `LYRDeletionModeMyDevices`.

#### Bug Fixes

* Fixes an issue where attempting to remove a participant would return `TRUE` when the participant was not a participant in the conversation.
* Fixes an issue that caused the `isSent` property of received messages to not get updated immediately upon receipt. 

## 0.17.7

#### Bug Fixes

* Fixes an issue where the `LYRClient` initializer would return nil in certain scenarios when an application is in the background.

## 0.17.6

#### Bug Fixes

* Fixes an issue where iOS would kill the app when kept in the background state for long enough.
* Fixes an issue where the SDK loses the accessibility of the database files in background when phone is locked and passcode protected, due to iOS data protection. A private build of "sqlite3" built with the SDK was replaced by using the system-wide available "sqlite3lib" library.

## 0.17.5

#### Public API changes

* Loosened the type constraint on `+clientWithAppID:` method to allow null returns.
* Fixed the conversation metadata generics (which was broken with the previous release of LayerKit).

#### Bug Fixes

* Fixes an issue where transitioning the app to background could cause a deadlock on the main thread.
* Fixes an issue where de-authenticating a client during a high activity of rich content transfers would crash the client.

## 0.17.4

#### Public API changes

* Added nullability annotations and type hints to the public API for Objective C generics.

#### Bug Fixes

* Fixes the issue where a locally deleted conversation gets restored without metadata.
* Fixes an issue which could prevent creating new conversations.
* Fixes compatibility issues with XCode 7.2.

#### Enhancements

* Client tries to keep the connection open even if the app gets completely suspended, which results in faster resumption when app is brought into the foreground.

## 0.17.3

#### Bug Fixes

* Improved stability of the SDK.
* Fixes the assertion issue related to receiving distinct conversations with the same set of participants after a conversation with the same set of participants was deleted.
* Fixes the issue that would cause the `Failed to persist a stream with client_id = nil` assertion.
* Fixes the intermittent conversation metadata update failures.
* Fixes a potential crash related with participant removal.
* Fixes the issue where deleting an active (chatty) conversation might raise an exception.

## 0.17.2

#### Enhancements

* Improved the performance of the cold synchronization process.
* Improved the memory footprint LayerKit makes in the cold sync scenarios and when the LYRClient needs to deal with a high volume of conversations.

#### Bug Fixes

* Fixed the potential crashes related to `UITableView` or `UICollectionView` that the `LYRQueryController` could cause by reporting incorrect number of objects.
* Fixed the `LYRPolicy` object's hashing logic, which helps collections identify the objects.
* Fixed memory leaks caused by LayerKit.
* Fixed bug which would prevent announcements from being marked as read.
* Conversations will now contain all metadata immediately after they are created.

## 0.17.1

#### Bug Fixes

* Fixed the observer crash when initializing the LYRClient and protected data is unavailable.
* `synchronizeWithRemoteNotification:completion:` now passes an error via completion block, in case the method is invoked while the app is in the foreground.
* Fixed an issue where announcements appeared as messages in its own conversation or weren't received at all.

#### Enhancements

* Synchronization process doesn't slow down anymore as conversations grow.

## 0.17.0

#### Dynamic Framework Support

`LayerKit 0.17.0` introduces support for distributing LayerKit as a [dynamic framework](http://blog.cocoapods.org/CocoaPods-0.36/). To prepare your project for dynamic framework support, please ensure you perform the following:

* Upgrade your local version of `CocoaPods` to `0.39.0` or greater.
* Add [`use_frameworks!`](https://guides.cocoapods.org/syntax/podfile.html#use_frameworks_bang) to the top of your `Podfile`.
* Ensure that your project's iOS deployment target is iOS 8.0 or greater. Dynamic frameworks are not supported prior to iOS 8.0.
* Change any `LayerKit` header import statements to following format: `<LayerKit/LayerKit.h>`. When building dynamic frameworks with `CocoaPods`, you may no longer use quoted imports.

#### Public API changes

* LayerKit client now uses message parts' MIMEType to resolve its filename extension for the rich content which is accessible through `(LYRMessagePart *)part.fileURL`.
* `LYRClientWillBeginSynchronizationNotification` now includes a progress object instance in the `userInfo` as the value to the `LYRClientSynchronizationProgressUserInfoKey`.
* Introduced `LYRPushNotificationConfiguration` for default and per recipient push notification configuration.
* The `LYRMessageOptionsPushNotificationAlertKey` and `LYRMessageOptionsPushNotificationPerRecipientConfigurationKey` keys have been deprecated for the `LYRMessageOptionsPushNotificationConfigurationKey` key, which takes an instance of `LYRPushNotificationConfiguration` to allow extended push customization.
* `LYRClientWillBeginSynchronizationNotification` now comes with a `userInfo` dictionary that contains an `LYRProgress` instance (under the `LYRClientContentTransferProgressUserInfoKey`) that tracks the progress of the cold-synchronization process.

#### Enhancements

* Rewritten the synchronization queuing logic that parallelizes processing per conversation.
* More reliable push notification handling when using the `synchronizeWithRemoteNotification:completion:` method
* Added support for building LayerKit as a dynamic framework.  
* Added support for bitcode.

## 0.16.0

#### Public API Changes

* `LYRQueryController` initialization on the `LYRClient` changes from `queryControllerWithQuery:` to `queryControllerWithQuery:error:` to return an error when the client isn't authenticated and a controller can't be created.
* `LYRQuery` now supports `LYRConversation` querying on property `metadata` in dictionary and key path forms.
* LayerKit client now tries to resolve message parts' MIMEType and uses an appropriate filename extension for the rich content `(LYRMessagePart *)part.fileURL`.

#### Bugfix

* Ensure `LYRMessagePart` `fileURL` property is updated when `LYRProgress` `fractionCompleted` is 1.
* Fixed `LayerKit` connection issue when XCode Product Name contained a unicode character.
* Fixed a minor memory leak when interacting with the Keychain APIs.

#### Enhancements

* Updated exception language when an invalid parameter is supplied to an `LYRQuery`.
* Updated error language when attempting to authenticate with an invalid nonce.
* Adding metadata querying support.

## 0.15.0

#### Public API Changes

* Changed `LYRClient` initializer to accept an `NSURL` object for the `appID` parameter.
* Changed `appID` property type from `NSUUID` to `NSURL` on `LYRClient`.

#### Enhancements

* Introduced file protection with `NSFileProtectionCompleteUntilFirstUserAuthentication` for all `LayerKit` files.

#### Bug Fixes

* Fixed an issue which caused a crash when calling `objectAtIndexPath:` on an empty `LYRQueryController`.

## 0.14.3

#### Enhancements

* When transitioning to background `LYRClient` now keeps the messaging services running for as long as iOS allows the app to run in the background.

#### Bug Fixes

* Fixes an issue where `LYRMessagePart`s hold outdated objects in memory, where updating it can throw exceptions due to mismatched version number.
* Fixes an issue where deleting conversation metadata at key path didn't work.
* Fixes an issue which caused LayerKit to indefinitely retry conversation creation after receiving an unrecoverable error from server.
* Fixes an issue where the `LYRClient` would auto-purge most of the downloaded content when setting the `client.diskCapacity` property.

## 0.14.2

#### Bug Fixes

* Fixes an issue where creating a query controller mutates a collection the client is enumerating.

## 0.14.1

#### Public API Changes

* Introduced `LYRConversation` query predicate and sort descriptor `lastMessage.sentAt`, which joins the already existing `lastMessage.receivedAt`.

#### Enhancements

* Added logic to speed up synchronization of conversation deletions and metadata updates.

#### Bug Fixes

* Fixes an issue where deleted conversations with pending changes caused the sync to completely stop.
* Fixes an issue where mutlitple local deletions and distinct conversation creations could create object cache inconsistencies and crash.
* Fixes an issue which caused `LayerKit` to return `nil` instead of `NSUIntegerMax` if an error occurred during a count query.

## 0.14.0

#### Enhancements

* Introduced Announcements, special Messages sent to all users of the application or to a list of users that will arrive outside of the context of a conversation. Announcements can only be sent through the Platform API.
* Introduced the ability to create a single distinct conversations between participants. This will prevent duplicate conversations if multiple users try to create conversations with each other at the same time. See Public API Changes for more details. Distinct conversations are now the default when creating new conversations. All conversations created before v0.14 are set to be non-distinct.

#### Public API Changes

* Added `LYRAnnouncement`, which models a platform message sent externally from any conversation.  `LYRAnnouncement` subclasses `LYRMessage` and is queryable by itself.  This works in conjunction with the Platform API.
* Added `LYRConversationOptionsDistinctByParticipantsKey` to `LYRConversation` as a key for the conversation `options` initilization parameter. Setting the value for this key to `YES` during initialization will guarantee that Layer only ever creates a single conversation for the specified participants. `YES` is also default if no options are specified.
* Added `isDistinct` property to `LYRConversation` to indicate whether or not the conversation is distinct by its participant list.

## 0.13.3

#### Public API Changes

* Introduced `LYRObjectChange`, which models a change that has occured upon a Layer model object. This object replaces the change dictionaries that `LYRClient` posted with change notifications.
* Deprecated the following object change dictionary keys: `LYRObjectChangeTypeKey`, `LYRObjectChangeObjectKey`, `LYRObjectChangePropertyKey`, `LYRObjectChangeOldValueKey`, `LYRObjectChangeNewValueKey`. Use the public properties on `LYRObjectChange` instead.

#### Enhancements

* Improved the performance of the Rich Content management (smaller memory footprint and CPU usage).
* Prioritized auto-download scheduling of message parts with Rich Content.

#### Bug Fixes

* Fixed crash caused by attempting to add a participant to a conversation they are already in.   
* Fixed crash caused by attempting to remove a participant from a conversation they are not in.
* Fixed crash when dealing with huge numbers of Rich Content parts.
* Fixed an issue where sent messages' recipient statuses seemed to be stuck on `LYRRecipientStatusPending`, even though messages were successfully sent.

## 0.13.2

#### Bug Fixes

* Fixed bug that prevented `LYRClient` objects from being properly deallocated.

## 0.13.2

#### Bug Fixes

* Fixed bug that would cause messages to not be marked as read when calling `markAllMessagesAsRead:` on `LYRConversation`.
* Fixed bug with object faulting causing message parts to be released.

## 0.13.1

#### Bug Fixes

* Fixed crash during synchronization caused by improperly set error pointers.
* Fixed crash during synchronization caused by fetching thousands of conversations at a time.
* Fixed crash caused by a Layer Client being deauthenticated while trying to mark messages as read.
* Fixed bug that could cause message recipient status to not update properly.

## 0.13.0

#### Enhancements

* Added the ability to receive messages from non-human actors via the Layer Platform API.
* Implemented partial object faulting to lower memory footprint.
* Added `LYRRecipientStatusPending` to the `LYRRecipientStatus` enumeration to align more closely with Layer Android SDK.

#### Bug Fixes

* Changed the behavior of `recipientStatusByUserID` such that the status for each recipient is `LYRRecipientStatusPending` rather than `LYRRecipientStatusSent` when a message is awaiting transport.

#### Public API Changes

* The `LYRMessage` property `sentByUserID` has been deprecated.
* The `LYRActor` object `sender` is a new property on `LYRMessage` to support non-human actors.  The `sender` has two mutually exclusive properties, `userID` and `name`.  `userID` is the user ID of a participant that sends a message, and `name` is the name specified from a platform non-human message sent in a conversation.

## 0.12.1

#### Bug Fixes

* Cleaned up numerous memory leaks across the sync engine and Rich Content manager.
* Fixed issues in the database access layer to avoid busy and lock errors under high concurrency.

## 0.12.0

#### Enhancements

* Changed several APIs to improve interoperability with Swift.
* Improved synchronization performance, if client has a lot of messages with rich content to sync.
* Improved message send times while performing sync.

#### Public API Changes

* The `LYQuery` initializer has been changed from `queryWithClass:` to `queryWithQueryableClass:`. This avoids the need to wrap `class` in backticks
when initializing a query object in Swift.
* The `LYRPredicate` initializer has been changed from `predicateWithProperty:operator:value:` to `predicateWithProperty:predicateOperator:value:`.
This avoids the need to wrap `operator` in backticks when initializing a predicate object in Swift.
* `updateRemoteNotificationDeviceToken:error:` now accepts a `nil` value as the `deviceToken` parameter. This un-registers devices from receiving push notifications.
* Multiple `LYRClient` instances created with the same appID are not allowed anymore, doing so will cause an assertion.
* Added `markMessagesAsRead:error:` to `LYRClient` to facilitate batch operations.
* Update `LYRMessagePart` initializers to enforce MIME Type format using the regular expression "/^[^\\s/]+/[^\\s/]+$/". This ensures that Rich Content message parts
do not get stuck during upload due to having an invalid MIME Type.

#### Bug Fixes

* Fixes an issue where background transfers only worked when device had sufficient power and a WiFi connection.
* Fixes a crash that occurs if `LYRClient` is instantiated under `XCTestCase` unit tests.
* Fixes an issue where a revived locally deleted conversation isn't operating correctly (previously it didn't include messages it had previously and didn't process public API requests correctly).
* Fixes an issue where `providerUserIDs` with slashes made the client crash, if in use with rich-content (content that is >2kb).
* Fixed an issue where metadata would synchronize incorrectly in certain cases. (Merged fix from maintenance release v0.9.10)

## 0.11.2

#### Enhancements

* Added new helper method to the query controller for looking up the index paths of objects given a set of identifiers.
* Integrated new logging and debugging facilities.

## 0.11.1

#### Bug Fixes

* Removes a Podfile change that was allowing LayerKit to be referenced as a transitive dependency in Swift projects when it would fail at build time.
* Fixed an issue where failed operations would fail to revert objects to their pre-error state.
* Fixed an issue where a deleted Conversation that received new Messages would fail to return to an active state.
* Reverted packaging changes that caused installation issues under non-CocoaPods installations.

## 0.11.0

This version of LayerKit includes a substantial change to Message ordering in order to enhance performance. Previous version of LayerKit utilized
a property named `index`, which was a monotonically increasing integer equal to the number of Messages that had been synchronized. From v0.11.0 on,
LayerKit maintains a new property named `position`. The `position` of a Message is a value that is calculated immediately when the Message is
synchronized and never changes. This greatly improves performance by reducing the change notification overhead associated with syncing large amounts
of Message content.

#### Public API Changes

* Dropped the `index` property on the `LYRMessage` object in favor of `position` which orders the messages in a conversation more efficiently.

#### Bug Fixes

* Fixes an issue where background transfers weren't handled in time, which caused the SDK to loose the downloaded file and retry the transfer.

## 0.10.3

#### Enhancements

* Changed distribution packaging to Dynamic iOS Framework.
* Compatibility with CocoaPods v0.36.0.

## 0.10.2

#### Enhancements

* Limited the number of Rich Content transfers that can be in flight at once to 5 uploads and 15 downloads.

#### Bug Fixes

* Fixed an issue where processing of pushed events could block the network thread, slowing down transport unnecessarily.

## 0.10.1

#### Bug Fixes

* Fixed an issue where some objects didn't had their properties changed, even though the changes coming from `layerClient:objectsDidChange:` in the dictionary dictated so.
* Fixed an issue where transitioning from foreground to background made `LYRProgress` instances stale (stopped tracking upload and download transfers).

## 0.10.0

This is a major new release of LayerKit that includes support for Rich Content. Rich Content is a large file or media asset
transported and synchronized by a new agent designed specifically to handle large payloads. Rich Content assets can be up to 2GB in size
and are handled transparently by the `LYRMessage` and `LYRMessagePart` models. Rich Content is discussed in detail in the
[v0.10.0 Transition Guide](http://developer.layer.com/docs/guides#richcontent).

#### Enhancements

* Added support for transporting messages with parts of up to 2GB in size.
* Added support for querying for `LYRMessagePart` objects.
* Added support for managing the disk space utilization of message parts.
* Added support for transfering the content of message parts while the app is in background via integration with the iOS Background Transfer Service.

#### Public API changes

* New property `autodownloadMIMETypes` on `LYRClient` which enables the client to automatically start the content downloads for message parts with specific MIME Types.
* New property `autodownloadMaximumContentSize` on `LYRClient` which enables the client to automatically start the content downloads for message parts that match the size criteria.
* New method `[LYRMessagePart downloadContent:]` which requests the client to manually download a message part.
* New method `[LYRMessagePart purgeContent:]` which requests the client to purge content from disk to save disk space (note: content is retrievable via downloadContent: method).
* New property `backgroundContentTransferEnabled` on `LYRClient` that enables support for background transfers.
* New method `[LYRClient handleBackgroundContentTransfersForSession:completion:]` used for background transfer handling.
* New property `diskCapacity` on `LYRClient` which provides support for disk utilization control.
* New property `currentDiskUtilization` on `LYRClient` which provides information on how much disk space is in use by message part content.
* New properties `transferStatus` and `progress` on `LYRMessagePart` that indicate the transfer state and its progress and `fileURL` that can be used to open the message part's content as file.
* New interface `LYRProgress` that tracks and reports progress of upload and download transfers.
* New interface `LYRAggregateProgress` meant for `LYRProgress` aggregation.

#### Bug Fixes

* The client will now suppress "Connection reset by peer" transport errors that occur when a connection is lost and reconnection is triggered.

## 0.9.10

#### Bug Fixes

* Fixed an issue where metadata would synchronize incorrectly in certain cases.

## 0.9.9

#### Bug Fixes

* Added countermeasures to ensure that multiple synchronization requests from rapidly delivered push notifications do not get lost.
* Backported a fix from 0.10.0 [110bdaa] that fixes the issue where an exception might be raised because of an internal race condition.

## 0.9.8

#### Bug Fixes

* The value of `receivedAt` is now set immediately upon send for `LYRMessage` objects. This improves sorting behaviors using the attribute.
* Locally deleted conversation weren't brought back, if client received new incoming messages.

## 0.9.7

#### Enhancements

* Introduced new `LYRPolicy` object for configuring communication policies. The first policy available is blocking, which enables users to block message delivery from other abusive users.

## 0.9.6

#### Bug Fixes

* The authenticated user is no longer implicitly included in the queried value for queries with the `LYRPredicateOperatorIsIn` or `LYRPredicateOperatorIsNotIn` operator on the `participants` property of the `LYRConversation` class. This prevents the query from erroneously matching or excluding all Conversations because the authenticated user is always a participant.
* Fixed `LYRQueryController` notifying its delegate that the query controller's content will/did change even when the changes do not affect the query controller's content.
* Fixed an issue where metadata change notifications would be published before the conversation had been created.
* Fixed an issue where transport state could get out of sync and result in messaging services being unavailable.
* Objects inserted outside the bounds of the pagination window of an `LYRQueryController` will no longer cause the pagination window to expand.
* Fixed an issue where removing a participant and adding them to a conversation back would fail.
* Fixed an issue where object changes would not be cleared after publication through certain codepaths. This could lead to duplicated changes or failure to notify of changes for properties that reverted to a previous value. This was most noticable on changes to `hasUnreadMessages` for Conversations, but could affect any changable property.
* Fixed an issue where querying for conversations with specific set of participants produced unpredictable results if some participants were removed from conversations.

## 0.9.5

#### Enhancements

* Introduced a new option for `LYRConversation` to allow developers to configure whether or not delivery receipts are generated on a per-conversation basis. This provides improved synchronization performance for conversations that do not utilize delivery receipts.

#### Bug Fixes

* Fixed an issue where locally deleted messages were not properly excluded from unread calculations.
* Fixed an issue where metadata changes would not trigger local change notifications or dispatch synchronization immediately upon change.
* Fixed an issue where metadata would attempt to synchronize for conversations that you are no longer a member of.

## 0.9.4

#### Public API changes

* The completion block of `LYRClient synchronizeWithRemoteNotification:completion:` has been changed. Instead of invoking the completion handler with a `UIBackgroundFetchResult` and an `NSError`, an `NSArray` of object changes and an `NSError` are now given. The `NSArray` contains `NSDictionary` instances that detail the exact changes made to the object model.

#### Enhancements

* The `LYRClient` class now includes a watchdog timer that ensures that connection and synchronization in response to push notifications does not exceed 15 seconds of wall clock time. This ensures that ample time is available for processing synchronized changes and prevents the application from being penalized by iOS for exceeding the 30 seconds allotted for processing the push.
* LayerKit now keeps its transport active on transition to the background for as long as permitted by iOS. This enables for the faster synchronization of incoming messages from push notifications.
* Object changes are now delivered directly to the push notification synchronization callback to facilitate easier processing.
* Enhanced the query controller by introducing the `paginationWindow` property, which enables simple pagination of the complete result set. This feature can be used to implement pull to refresh, "Load More" buttons, or automatic loading of additional objects during scrolling. See the comments on the `LYRQueryController` class for more details.
* Enhanced the query controller by introducing the `updatableProperties` property, which provides control over which properties should generate update notifications. This can be used to enhance UI performance through the elision of uninteresting updates. See the comments on the `LYRQueryController` class for more details.
* Added new `diagnosticDescription` method to `LYRClient` that dumps a report of the client's internal state for debugging. This method is not in the public header, but can be invoked via `valueForKeyPath:`.

#### Bug Fixes

* Fixed an issue where LayerKit would not shut down transport after succesfully connecting and sychronizing in response to a push notification.
* Fixed an issue where authentication challenges encountered by transport were not handled properly.
* Fixed an issue where LayerKit would not emit a callback from `synchronizeWithRemoteNotification:completion:` if a connection could not be established.
* Fixes an issue where the query controller would emit unnecessary update notifications for objects that were created or deleted.

## 0.9.3

#### Enhancements

* The `sentByUserID` property of `LYRMessage` objects is now populated immediately upon send.
* The `LYRQuery` class now includes a detailed `description` implementation that describes the query.
* Added support for importing LayerKit into Swift based projects using CocoaPods v0.36.0+ by including umbrella module header.

#### Bug Fixes

* The `receivedAt` time is now set immediately upon message delivery.
* The query controller now dispatches move events for queries against `lastMessage.receivedAt`.
* Fixed a crash when an attempt is made to mark all messages read on a conversation that has been concurrently deleted.
* Fixed an issue that could result in changes failing to be merged onto in memory objects.
* All methods on `LYRClient` that cannot be used when unauthenticated now return appropriate errors.
* Fixed an issue where previously deleted metadata keys would fail to synchronize when subsequently restored by setting a new value.
* Updated several `LYRClient` authentication delegate callbacks to guarantee invocation on the main thread.

## 0.9.2

#### Enhancements

* Improved concurrency and error handling in the persistence layer.
* Added `canonicalObjectIdentifierForIdentifier:` to `LYRClient` to help with migrating externally stored object identifier references to the new schema.
* Synchronization in response to remote notification via `synchronizeWithRemoteNotification:completion:` now guarantees delivery of the completion callback on the main thread.

#### Bug Fixes

* Fixed a SQLite build issue that increased exposure to database busy / locked errors.
* SQLite busy / locked errors are now immediately propagated back from any query that encounters them, ensuring queries and result sets completely succeed or fail.
* Attempts to set metadata on key-paths where the nested parents did not yet exist would fail silently. These intermediate nesting dictionaries are now created.

## 0.9.1

#### Enhancements

* The synchronization engine integration with transport has been simplified and enhanced for more reliable behavior under poor network conditions.
* Added querying support on `lastMessage.receivedAt` from `LYRConversation`
* Performance was improved by offloading processing from the network thread.
* The `receivedAt` property for `LYRMessage` objects sent by the current user is no longer `nil`. It is now set to the same timestamp as `sentAt`.
* Querying against `LYRConversation` participants now implicitly includes the authenticated user.

#### Bug Fixes

* `LYRClient` objects will now attempt to reconnect immediately upon losing a connection even if reachability state has not changed.
* An issue where synchronization could become stalled when the app returned from the background has been fixed.
* Fixed an issue where metadata values were not validated properly, blocking the use of nested structures.
* Fixed an issue where `isUnread` and `hasUnreadMessages` did not always update appropriately during synchronization.
* Fixed an issue where `LYRConversation` objects returned via querying had a `lastMessage` value of `nil`.
* Fixed an issue that could result in database busy errors and crashes during concurrent database transactions.
* Fixed an issue where typing indicator received before a conversation was synchronized would result in a crash.
* Fixed a regression in querying for participants with certain structures of user identifiers.

#### Public API changes

## 0.9.0

LayerKit v0.9.0 includes numerous feature enhancements and API changes in preparation for the upcoming 1.0 release. The API changes were made to
make LayerKit more intuitive and prepare for future platform enhancements. These changes are detailed in the LayerKit [Transition Guide](https://developer.layer.com/docs/transition/ios).

#### Public API changes

* Layer object initializers were changed such that Conversations and Messages must now be initialized through the client instead of directly via the class. This change enables object identifiers to be populated earlier and is part of a larger migration of functionality from the client onto the model objects themselves.
* `[LYRConversation conversationWithParticipants:]` has been deprecated in favor of `[LYRClient conversationWithParticipants:options:error:]`.
* `[LYRMessage messageWithConversation:parts:]` has been deprecated in favor of `[LYRClient newConversationWithParticipants:options:error:]`.
* `[LYRMessage messageWithConversation:parts:]` has been deprecated in favor of `[LYRClient newMessageWithConversation:parts:options:error:]`.
* Push Notification alert text and sounds can now be assigned at Message initialization time via the `options:` argument.
* `[LYRClient setMetadata:onObject:]` has been deprecated in favor of the `LYRMessage` options and `LYRConversation` mutable metadata API's.
* `[LYRClient addParticipants:toConversation:error:]` has been deprecated in favor of `[LYRConversation addParticipants:error:]`.
* `[LYRClient removeParticipants:fromConversation:error:]` has been deprecated in favor of `[LYRConversation removeParticipants:error:]`.
* `[LYRClient sendMessage:error:]` has been deprecated in favor of `[LYRConversation sendMessage:error:]`.
* `[LYRClient markMessageAsRead:error:]` has been deprecated in favor of `[LYRMessage markAsRead:]`.
* `[LYRClient deleteMessage:mode:error:]` has been deprecated in favor of `[LYRMessage delete:error:]`.
* `[LYRClient deleteConversation:mode:error:]` has been deprecated in favor of `[LYRConversation delete:error:]`.
* `[LYRClient sendTypingIndicator:toConversation:]` has been deprecated in favor of `[LYRConversation sendTypingIndicator:]`;
* `[LYRClient conversationForIdentifier:]` has been deprecated, use querying support to fetch conversations based on identifier.
* `[LYRClient conversationsForIdentifiers:]` has been deprecated, use querying support to fetch conversations based on a set of identifiers.
* `[LYRClient conversationsForParticipants:]` has been deprecated, use querying support to fetch conversations based on a set of participants.
* `[LYRClient messagesForIdentifiers:]` has been deprecated, use querying support to fetch messages based on a given set of identifiers.
* `[LYRClient messagesForConversation:]` has been deprecated, use querying support to fetch messages for specific conversation.
* `[LYRClient countOfConversationsWithUnreadMessages:]` has been deprecated, use querying support to count all unread messages.
* `[LYRClient countOfUnreadMessagesInConversation:]` has been deprecated, use querying support to count unread messages for given conversation.
* `LYRMessage` and `LYRConversation` objects now use a consistent identifier scheme that won't change.
* `LYRMessagePushNotificationAlertMessageKey` key constant has been deprecated in favor of `LYRMessageOptionsPushNotificationAlertKey`.
* `LYRMessagePushNotificationSoundNameKey` key constant has been deprecated in favor of `LYRMessageOptionsPushNotificationSoundNameKey`.

#### Enhancements

* `LYRConversation` now supports synchronized, mutable developer assigned metadata. Metadata is synchronized across participants on a per-key basis using last writer wins semantics. See the header documentation on `LYRConversation` for details of the API.
* Added querying for conversations and messages, see `LYRQuery` and `LYRPredicate`.
* Added query controller that can be used to drive the UI, see `LYRQueryController`.

#### Bug Fixes

* Fixes an issue where the LYRClient might crash when detecting a remotely deleted conversation leaving the client with unsent changes that fail to get reconciled.
* Fixed an issue where push device tokens would not be updated after a connection was established in some circumstances.

## 0.8.8

#### Bug Fixes

* Fixes an issue where LYRClient might crash if a user had deleted a conversation locally and then received a global deletion of a conversation caused by other participant.
* Fixes an issue where LYRClient might produce two different object instances when fetching objects.
* Fixes an issue where LYRClient wasn't capable of receiving pushed events via transport after transitioning into an active application state.
* Fixes an issue where LYRClient crashed when dealing with outdated membership changes for deleted conversations.
* Fixes an issue where LYRClient crashed when allocating the work load across synchronization cycles.
* Fixes an issue where LYRClient tried to open push channel even when in unauthenticated state.

## 0.8.7

#### Enhancements

* Added typing indicators, see LYRClient.h for more details.
* Enhanced connection management to handle connectivity situations where the server is reachable but unresponsive.

#### Bug Fixes

* `LYRClient` now schedules a synchronization process as the `UIApplication` becomes active.
* Message recipient status change notification behavior was updated to be more predictable and consistent.
* Fixed an issue with the calculation of message part size limits.
* Session state is now segregated by appID, facilitating graceful authentication handling when switching between appID's (i.e. between staging and production).
* Fixed an issue in the storage of user identifiers that could result in incorrect querying by participants for applications that use very large numeric values for user ID's.

## 0.8.6

#### Bug Fixes

* Ensure that Layer managed database files have the `NSURLIsExcludedFromBackupKey` resource value applied.

## 0.8.5

#### Bug Fixes

* Fixes an issue when querying against certain sets of participant user identifiers.

## 0.8.4

#### Bug Fixes

* Removed a faulty migration file from the resources bundle.

## 0.8.3

#### Public API changes

* `layerClient:didFinishSynchronizationWithChanges` changed to `layerClient:objectsDidChange:`
* `layerClient:didFailSynchronizationWithError` changed to `layerClient:didFailOperationWithError:`
* `deleteConversation:error:` changed to `deleteConversation:mode:error:`
* `deleteMessage:error:` changed to `deleteMessage:mode:error:`

#### Enhancements

* Improved stability and performance around the synchronization process.
* Improved performance on public API methods.
* Added support for local object deletion (see LYRClient.h for more info).
* Performing conversation and message fetches from different threads doesn't cause them to lock anymore.
* `LYRClient` now manages connection state.
* `LYRClient` now reports more friendly network errors.

#### Bug Fixes

* Fixed an issue where the `lastMessage` property didn't get updated regularly.
* Fixed an issue where it occasionally caused an DATABASE BUSY log warning.

## 0.8.2

#### Bug Fixes

* Fixed the "Database in use" warnings.
* Fixed an issue where frequent calls to markMessageAsRead on the same object caused an EXC_BAD_ACCESS error.
* Added countermeasures to prevent synchronization of duplicate conversations and messages.
* LayerKit doesn't raise an exception if user de-authenticates during a synchronization process.

## 0.8.1

#### Bug Fixes

* Fixed a symbol collision with a third-party dependency.

## 0.8.0

#### Enhancements

* Updated LayerKit to communicate with the new developer.layer.com environment.
* Added `isConnecting` to the `LYRClient` public API for introspecting connection status.

#### Bug Fixes

* Assertion on an intermittent bug that is very hard to reproduce. We encourage developers to send us the crash report (the traced error message, exception and the stack trace).
* Improved handling of Push Notifications when transitioning between active, inactive, and background states.
* LYRClient now calls the `layerClient:didFinishSynchronizationWithChanges:` delegate method even if there weren't any changes.
* LYRClient now validates for the maximum number of participants in `sendMessage:` and `addParticipants:` method.
* Fixed an issue where the LYRClient would crash if it received a `nil` message part data.
* LayerKit will now properly handle transport of zero length message parts.

## 0.7.21

#### Bug Fixes

* Improved handling of Layer platform push events while executing in the background.
* Fixed an issue where user generated object identifiers with lowercase strings weren't recognized by `conversationForIdentifiers` or `messagesForIdentifiers`.

## 0.7.21-rc1

#### Bug Fixes

* Fixed a potential crash when the client is asked to establish a connection while a connection attempt is already in progress.

## 0.7.19

#### Enhancements

* Reduced the number of reads in the synchronization process.
* Synchronization work load more consistent across synchronization cycles.
* Improved performance in internal pattern matching logic.

## 0.7.18

#### Bug Fixes

* Fixed an issue where `setMetadata:forObject` queued the message for sending.
* Fixed an intermittent issue where a message got stuck at the end of the conversation forever.

## 0.7.17

#### Enhancements

* Synchronization process doesn't block fetching methods anymore.

#### Bug Fixes

* Fixed an issue where fetching objects during synchronization caused incomplete mutations.

## 0.7.16

#### Bug Fixes

* Fixed an issue where deleted messages brought the conversation into an inconsistent state.
* Fixed an issue where in some situations `lastMessage` property didn't get updated.
* Fixed an issue where conversation synchronization aborted due to a network error resulted in local conversation deletion.
* Fixed an issue where the transport became unresponsive for a moment.

## 0.7.15

#### Enhancements

* Improved performance when synchronizing large data sets.
* Enhanced concurrency and cancellation behaviors in synchronization engine.

#### Bug Fixes

* Fixed SQL errors logged due to persistence of duplicated delivery and read receipts.
* Fixed an error when an attempt is made to delete a Conversation that was already deleted by another participant.
* Fixed an issue where the `sentAt` timestamp was incorrectly truncated on 32 bit processors.
* Fixed several Keychain Services errors.
* Fixed an issue where Push Notification device tokens were not guaranteed to be transmitted across authentication changes.
* Fixed an intermittent issue where `conversationsForParticipants:` could inappropriately return `nil`.
* `LYRClient` delegate method `layerClient:didFailSynchronizationWithError:` now only reports a single error if synchronization fails.

## 0.7.14

#### Enhancements

* LayerKit is now compatible with iOS 8 on an experimental basis.

#### Bug Fixes

* Fix exception related to marking messages as read.

## 0.7.13

#### Enhancements

* All public API methods that accept a collection now perform type checks to provide clear feedback on input violations.

#### Bug Fixes

* LYRClient reports unprocessable pushed payloads via `layerClient:didFailSynchronizationWithError:`.
* The sync engine will no longer attempt to write delivery receipts when you are no longer a participant in a Conversation.
* conversationsForParticipants: didn't fetch any conversations.

## 0.7.12

#### API changes

* Method `conversationForParticipants:` which returned a single result, changed to `conversationsForParticipants:` which now returns a set of conversations.
* `LYRMessage`'s `recipientStatusByUserID` property now populated immediately after the `sendMessage:` call.
* LYRConversation's `conversationWithParticipants:` method now accepts an `NSSet` instead of an `NSArray` of participants.
* LYRClient's `conversationsForParticipants:` method now accepts an `NSSet` instead of an `NSArray` of participants.
* LYRClient's `addParticipants:toConversation:error:` method now accepts an `NSSet` instead of an `NSArray` of participants.
* LYRClient's `removeParticipants:fromConversation:error:` method now accepts an `NSSet` instead of an `NSArray` of participants.

#### Enhancements

* Many API methods on `LYRClient` will now validate authentication state and log warnings when invoked from an unauthenticated state.
* `LYRClient` will now enforce a single authentication request limit. If concurrent authentication cycles are begun the latest request will cancel its predecessors.

#### Bug Fixes

* Attempts to authenticate while already connected will now return errors.
* Silent push notifications no longer start synchronization.
* Fixed an issue where incorrect conversations could be returned by `conversationForParticipants:`.
* Object change notifications will no longer return non-uniqued instances of a given object.
* Receivers don't generate delivery events anymore for messages already marked as delivered or read.
* `conversationsForParticipants:` will now implicitly include the current user in the queried set.
* Fixed an issue where messages sent during a synchronization process had incorrect index values.

## 0.7.11

#### Enhancements

* Distribution is now done via an .embeddedframework for easier non-CocoaPods installation.

#### Bug Fixes

* Fixed an issue with incorrect message ordering.
* Ensure that 64bit values are handled consistently across CPU architectures.
* Fixed a race condition that could result in multiple connection attempts from the client during push notifications.
* Ensure that the deauthentication callback is always delivered on the main thread.

## 0.7.10

#### Bug Fixes

* Miscellaneous internal bug fixes.

## 0.7.9

#### Enhancements

* Deauthentication now includes a completion callback.

#### Bug Fixes

* Ensure that `createdAt` is populated on `LYRConversation` objects
* Fixed issue wherein timestamp properties were incorrectly populated with the Epoch date.
* Fixed an issue where `lastMessage` could be nil during change notifications.
* The `LYRClient` delegate will no longer receive authentication challenge callbacks during initial connection (as documented).

## 0.7.8

#### Bug Fixes

* Fix issue with updating Push Notification tokens.

## 0.7.7

#### Bug Fixes

* Push Notification synchronization callbacks are now guaranteed delivery on the main thread, avoiding potential crashes.

## 0.7.6

#### Enhancements

* Internal improvements to client/server configuration negotiation.

## 0.7.5

#### Enhancements

* Message creation notifications are now delivered ahead of updates.

## 0.7.4

Initial preview release of LayerKit.
