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
