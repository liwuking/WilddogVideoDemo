//
//  Wilddog.h
//  Wilddog
//
//  Created by Garin on 15/7/7.
//  Copyright (c) 2015年 Wilddog. All rights reserved.
//

#import "WQuery.h"
#import "WDataSnapshot.h"
#import "WilddogApp.h"
#import "WConfig.h"
#import "WTransactionResult.h"
#import "WMutableData.h"

NS_ASSUME_NONNULL_BEGIN

/**
 *
 */
@interface Wilddog : WQuery


/** @name 初始化一个 Wilddog 对象 */


/**
 *  初始化一个由 url 生成的对象。
 *
 *  @param url  URL(例如: https://<appId>.wilddogio.com/)
 *
 */
- (id)initWithUrl:(NSString *)url;


/** @name 获取子节点路径 */


/**
 *
 *  获得一个在指定的相对路径节点的Wilddog对象。
 *
 *  相对路径可以是一个简单的节点名字（例如，‘fred’）
 *  或者是一个更深的路径（例如，'fred/name/first'）
 *
 *  @param pathString 从这个节点到要设定的子节点的相对路径
 *
 *  @return 指定节点位置的Wilddog对象
 */
- (Wilddog *)childByAppendingPath:(NSString *)pathString;


/**
 *  childByAutoId 生成一个唯一名字的子节点，并且返回一个Wilddog对象
 *
 *  @return 指定节点位置的Wilddog对象
 */
- (Wilddog *)childByAutoId;


/** @name 数据操作 */


/*!  往 Wilddog 当前路径写入一个值.
 
 这将会覆盖当前路径和子路径的所有数据.
 
 支持的数据类型:
 
 - NSString -- @"Hello World"
 - NSNumber (包括BOOL类型) -- @YES, @43, @4.333
 - NSDictionary -- @{@"key": @"value", @"nested": @{@"another": @"value"} }
 - NSArray
 
 传送一个nil或者null对象相当于调用 `removeValue`;
 这个路径的所有数据和子路径的数据都将被删除.
 
 `setValue:` 将会删除先前保存的 priority，所以如果要保留先前 priority，必须调用 setValue:andPriority:
 
 `Server Timestamps:` Wilddog 服务器提供一种机制来获取服务器时间。比如我们可以结合 *onDisconnect* 来记录一个客户端的下线时间。
 
    Wilddog *userLastOnlineRef = [[Wilddog alloc] initWithUrl:@"https://<YOUR-WILDDOG-APP>.wilddogio.com/users/joe/lastOnline"];
    [userLastOnlineRef onDisconnectSetValue:kWilddogServerValueTimestamp];
 
 @param value 将被传送的值.
 
 
 */
- (void)setValue:(nullable id)value;


#define kWilddogServerValueTimestamp @{ @".sv": @"timestamp" }

/**
 *  同 setValue: 方法类似：增加了一个 block，当写操作完成之后，会回调这个 block。
 *
 *  @param value 将被写入的值
 *  @param block 写操作提交到 Wilddog 服务器后回调的 block
 *  @see setValue:
 */
- (void)setValue:(nullable id)value withCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/**
 * 和 setValue: 方法类似，只是为要写入的数值添加了一个优先级
 *
 * 优先级被用来排序
 *
 * @param value 要写入的数值
 * @param priority 这个数值的优先级
 *
 * @see setValue:
 */
- (void)setValue:(nullable id)value andPriority:(nullable id)priority;


/**
 * 与 setValue:andPriority: 方法类似，当写操作被提交到服务器，这个block将被触发
 *
 * @param value 要写入的数值
 * @param priority 这个数值的优先级
 * @param block 当写操作被提交到服务器，将被触发的block
 *
 *  @see setValue:
 */
- (void)setValue:(nullable id)value andPriority:(nullable id)priority withCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/**
 *  删除当前节点，效果等同于 setValue:nil；
 *
 *  如果父级节点只有当前节点一个子节点，会递归删除父级节点。
 */
- (void)removeValue;


/**
 *  同remove方法类似：增加了一个block，当删除操作完成之后，会回调这个block。
 *
 *  @param block 删除操作提交到Wilddog服务器后，返回的block
 */
- (void)removeValueWithCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/**
 *  设置Wilddog当前节点的优先级。
 *  优先级被用来排序（如果没有指定优先级，子节点按照key排序）。
 *
 *  你不能对一个不存在的节点设置优先级。因此，当为新数据设置指定的优先级的时候，使用setValue:andPriority: ，当为已存在的数据指定优先级的时候，使用setPriority:。
 *
 *  节点按照如下规则排序：
 *  没有priority的排最先。
 *  有数字priority的次之，按照数值排序(从小到大)。
 *  有字符串 priority的排最后，按照字母表的顺序排列。
 *  当两个子节点有相同的 priority（包括没有priority），它们按照名字进行排列，数字排在最先（按数值大小排序），其他的跟在后面(以字典序排序)。
 * 
 *  注意：数值优先级被作为IEEE 754双精度浮点型数字进行解析和排序，Key以String类型进行存储，只有当它能被解析成32位整型数字时被当作数字来处理。
 *
 *  @param priority  指定节点的优先级。
 */
- (void)setPriority:(nullable id)priority;


/**
 * 和 setPriority: 方法类似，增加了一个block，当priority操作被提交到Wilddog服务器之后，会回调这个block。
 *
 * @param priority 指定节点的优先级
 * @param block 当priority操作被提交到Wilddog服务器之后，回调的block
 */
- (void)setPriority:(nullable id)priority withCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/**
 *  将输入对象的子节点合并到当前数据中。
 *
 *  不存在的子节点将会被新增，存在子节点将会被替换。
 *  与set操作不同，update 不会直接覆盖原来的节点，而是将value 中的所有子节点插入到已有的节点中，如果已有的节点中已经有同名子节点，则覆盖原有的子节点。
 *   例如： update之前 {"l1":"on","l3":"off"} ,value={"l1":"off","l2":"on"} update 后的数据是 {"l1":"off","l2":"on","l3":"off"}。
 *
 *  @param values 包含要合并子节点的对象
 */
- (void)updateChildValues:(NSDictionary *)values;


/**
 *  同updateChildValues方法类似：增加了一个block，当更新操作完成之后，会回调这个block。
 *
 *  @param values 包含要合并子节点的对象
 *  @param block updateChildValues 操作提交到 Wilddog 服务器后，返回的block
 */
- (void)updateChildValues:(NSDictionary *)values withCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/** @name 监听数据变化，读取数据 */


/**
 *  observeEventType:withBlock: 用于监听一个指定节点的数据变化.
 *
 *
 *  这是从Wilddog服务器读取数据的主要方式.如果这个路径数据有变化，block将会被调用。另外，WEventTypeChildAdded, WEventTypeChildMoved, 和
 *  WEventTypeChildChanged 事件将会传回前一节点的 Key 回来。（由 priority 排序）
 *
 *  使用 removeObserverWithHandle: 来停止接受数据.
 *
 *  @see WEventType
 *  @param eventType 监听的事件类型
 *  @param block     当监听到某事件时，回调block
 *
 *  @return 一个WilddogHandle，用于调用函数 removeObserverWithHandle: 去注销这个block
 */
- (WilddogHandle)observeEventType:(WEventType)eventType withBlock:(void (^)(WDataSnapshot* snapshot))block;


/**
 * observeEventType:andPreviousSiblingKeyWithBlock: 用于监听在特定节点处的数据的变化。
 * 这是从Wilddog数据库读取数据的主要方法。block当监听到初始数据和初始数据有改变时触发。 此外， 对于 WEventTypeChildAdded, WEventTypeChildMoved, 和 WEventTypeChildChanged 事件, block通过priority排序将传输前一节点的key值。
 *
 * 用 removeObserverWithHandle: 方法去停止接受数据更新的监听。
 *
 * @param eventType 监听的事件类型
 * @param block 当监听到初始数据和初始数据发生变化时，这个block将被回调。block将传输一个WDataSnapshot类型的数据和前一个子节点的key
 * @return 一个WilddogHandle，用于调用函数 removeObserverWithHandle: 去注销这个block
 */
- (WilddogHandle)observeEventType:(WEventType)eventType andPreviousSiblingKeyWithBlock:(void (^)(WDataSnapshot* snapshot, NSString *__nullable  prevKey))block;


/**
 *  observeEventType:withBlock: 用于监听一个指定节点的数据变化
 *  这是从Wilddog服务器读取数据的主要方式，block当监听到初始数据和初始数据有改变时触发。
 *  由于你没有读取权限，就接受不到新的事件，那么cancelBlock就会被调用
 *
 *  @param eventType   监听的事件类型
 *  @param block       当监听到某事件时，回调block
 *  @param cancelBlock 如果客户端没有权限去接受这些事件，这个block将会被调用
 *
 *  @return 一个WilddogHandle，用于调用函数 removeObserverWithHandle: 去注销这个block
 */
- (WilddogHandle)observeEventType:(WEventType)eventType withBlock:(void (^)(WDataSnapshot* snapshot))block withCancelBlock:(nullable void (^)(NSError* error))cancelBlock;


/**
 * observeEventType:andPreviousSiblingKeyWithBlock: 用于监听在特定节点处的数据的变化。
 * 这是从Wilddog数据库读取数据的主要方法。block当监听到初始数据和初始数据有改变时触发。 此外， 对于 WEventTypeChildAdded, WEventTypeChildMoved, 和 WEventTypeChildChanged 事件, block通过priority排序将传输前一节点的key值。
 *
 * 由于你没有读取权限，就接受不到新的事件，这时cancelBlock就会被调用
 *
 * 用 removeObserverWithHandle: 方法去停止接受数据更新的监听。
 *
 * @param eventType 监听的事件类型
 * @param block 当监听到初始数据和初始数据发生变化时，这个block将被回调。block将传输一个WDataSnapshot类型的数据和前一个子节点的key
 * @param cancelBlock 如果客户端没有权限去接受这些事件，这个block将会被调用
 *
 * @return  一个WilddogHandle，用于调用函数 removeObserverWithHandle: 去注销这个block
 */
- (WilddogHandle)observeEventType:(WEventType)eventType andPreviousSiblingKeyWithBlock:(void (^)(WDataSnapshot* snapshot, NSString *__nullable prevKey))block withCancelBlock:(nullable void (^)(NSError* error))cancelBlock;


/**
 *  同observeEventType:withBlock: 类似，不同之处在于 observeSingleEventOfType:withBlock: 中的回调函数只被执行一次。
 *
 *  @param eventType 监听的事件类型
 *  @param block     当监听到某事件时，回调block
 */
- (void)observeSingleEventOfType:(WEventType)eventType withBlock:(void (^)(WDataSnapshot* snapshot))block;


/**
 * 这个方法和 observeEventType:withBlock: 方法类似。不同之处是：在初始数据返回后，这个block回调一次就被取消监听。 此外， 对于 WEventTypeChildAdded, WEventTypeChildMoved, 和 WEventTypeChildChanged 事件, block通过priority排序将传输前一节点的key值。
 *
 * @param eventType 监听的事件类型
 * @param block block 当监听到初始数据和初始数据发生变化时，这个block将被回调。block将传输一个WDataSnapshot类型的数据和前一个子节点的key
 */
- (void)observeSingleEventOfType:(WEventType)eventType andPreviousSiblingKeyWithBlock:(void (^)(WDataSnapshot* snapshot, NSString *__nullable prevKey))block;


/**
 *  同observeSingleEventOfType:withBlock:类似，如果你没有在这个节点读取数据的权限，cancelBlock将会被回调
 *
 *  @param eventType   监听的事件类型
 *  @param block       当监听到某事件时，回调block
 *  @param cancelBlock 如果您没有权限访问此数据，将调用该cancelBlock
 */
- (void)observeSingleEventOfType:(WEventType)eventType withBlock:(void (^)(WDataSnapshot* snapshot))block withCancelBlock:(nullable void (^)(NSError* error))cancelBlock;


/**
 * 这个方法和 observeEventType:withBlock: 方法类似。不同之处是：在初始数据返回后，这个block回调一次就被取消监听。 此外， 对于 WEventTypeChildAdded, WEventTypeChildMoved, 和 WEventTypeChildChanged 事件, block通过priority排序将传输前一节点的key值。
 *
 * 如果你没有在这个节点读取数据的权限，cancelBlock将会被回调
 *
 * @param eventType 监听的事件类型
 * @param block 将传输一个WDataSnapshot类型的数据和前一个子节点的key
 * @param 如果您没有权限访问此数据，将调用该cancelBlock
 */
- (void)observeSingleEventOfType:(WEventType)eventType andPreviousSiblingKeyWithBlock:(void (^)(WDataSnapshot* snapshot, NSString *__nullable prevKey))block withCancelBlock:(nullable void (^)(NSError* error))cancelBlock;



/** @name 移除数据监听 */


/**
 *  取消监听事件。取消之前用observeEventType:withBlock:方法注册的监听事件。
 *
 *  @param handle 由observeEventType:withBlock:返回的 WilddogHandle
 */
- (void)removeObserverWithHandle:(WilddogHandle)handle;


/**
 *  取消之前由 observeEventType:withBlock:方法注册的监听事件。
 */
- (void)removeAllObservers;


/** @name 离线操作 */


/**
 * 离线操作的含义是客户端的推送的数据并非立刻生效,而是当客户端离线的时候才生效。
 *
 * 当客户端失去连接（因为关闭浏览器，导航一个新的页面，或者网络出现问题）时，确保在该节点的数据被设置成我们未离线前设定的值。
 *
 * onDisconnectSetValue: 方法对实现在线系统是很有用的，这个在线系统可理解为：当用户失去连接时，一个数值被改变或者被清除，在别人的角度看，他的状态会显示“离线”。
 *
 * @param value 断开连接后要设置的值
 */
- (void)onDisconnectSetValue:(nullable id)value;


/**
 * 离线操作的含义是客户端的推送的数据并非立刻生效,而是当客户端离线的时候才生效。
 *
 * 当客户端失去连接（因为关闭浏览器，导航一个新的页面，或者网络出现问题）时，确保在该节点的数据被设置成我们未离线前设定的值。
 *
 * @param value 断开连接后要设置的值
 * @param block 当设置值的操作成功排队到Wilddog服务器上，这个block就会被触发
 */
- (void)onDisconnectSetValue:(nullable id)value withCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/**
 * 离线操作的含义是客户端的推送的数据并非立刻生效,而是当客户端离线的时候才生效。
 *
 * 当客户端失去连接（因为关闭浏览器，导航一个新的页面，或者网络出现问题）时，确保在该节点的数据被设置成我们未离线前设定的值和优先级。
 *
 * @param value 断开连接后要设置的值
 * @param priority 断开连接后要设置的优先级
 */
- (void)onDisconnectSetValue:(nullable id)value andPriority:(id)priority;


/**
 * 离线操作的含义是客户端的推送的数据并非立刻生效,而是当客户端离线的时候才生效。
 *
 * 当客户端失去连接（因为关闭浏览器，导航一个新的页面，或者网络出现问题）时，确保在该节点的数据被设置成我们未离线前设定的值和优先级。
 *
 * @param value 连接断开后要设置的值
 * @param priority 连接断开后要设置的优先级
 * @param block 当设置值的操作成功排队到Wilddog服务器上，这个block就会被触发
 */
- (void)onDisconnectSetValue:(nullable id)value andPriority:(nullable id)priority withCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/**
 * 离线操作的含义是客户端的推送的数据并非立刻生效,而是当客户端离线的时候才生效。
 *
 * 当客户端失去连接（因为关闭app，导航一个新的页面，或者网络出现问题）时，确保在该节点的数据被删除。
 *
 * onDisconnectRemoveValue 对实施在线系统很有用
 */
- (void)onDisconnectRemoveValue;


/**
 * 离线操作的含义是客户端的推送的数据并非立刻生效,而是当客户端离线的时候才生效。
 *
 * 当客户端失去连接（因为关闭app，导航一个新的页面，或者网络出现问题）时，确保在该节点的数据被删除。
 *
 * onDisconnectRemoveValueWithCompletionBlock: 对实施在线系统很有用
 *
 * @param block 当删除值的操作成功排队到Wilddog服务器上，这个block就会被触发
 */
- (void)onDisconnectRemoveValueWithCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/**
 * 离线操作的含义是客户端的推送的数据并非立刻生效,而是当客户端离线的时候才生效。
 *
 * 当客户端失去连接（因为关闭浏览器，导航一个新的页面，或者网络出现问题）时，确保拥有子节点的数据被更新。
 *
 * @param values 在连接断开之后，一个包含子节点键和值的字典
 */
- (void)onDisconnectUpdateChildValues:(NSDictionary *)values;


/**
 * 离线操作的含义是客户端的推送的数据并非立刻生效,而是当客户端离线的时候才生效。
 *
 * 当客户端失去连接（因为关闭浏览器，导航一个新的页面，或者网络出现问题）时，确保拥有子节点的数据被更新。
 *
 * @param values 在连接断开之后，一个包含子节点键和值的字典
 * @param block 当更新值的操作成功排队到Wilddog服务器上，这个block就会被触发
 */
- (void)onDisconnectUpdateChildValues:(NSDictionary *)values withCompletionBlock:(void (^)(NSError *__nullable error, Wilddog* ref))block;


/**
 * 取消运行在离线状态设置的所有操作。
 * 如果你之前调用了 onDisconnectSetValue:,onDisconnectRemoveValue:, 或者 onDisconnectUpdateChildValues: 方法, 并且当连接断开时，不想再更新数值，这时候就调用cancelDisconnectOperations:方法。
 *
 */
- (void)cancelDisconnectOperations;


/**
 * 取消运行在离线状态设置的所有操作。 
 * 如果之前调用了 onDisconnectSetValue: ,onDisconnectRemoveValue: , or onDisconnectUpdateChildValues: 方法, 并且在连接断开后，不再想要更新数据，请调用cancelDisconnectOperations:方法。
 *
 * @param block 当Wilddog服务器接受到cancel请求，触发的block
 */
- (void)cancelDisconnectOperationsWithCompletionBlock:(nullable void (^)(NSError *__nullable error, Wilddog* ref))block;


/** @name 手动连接管理 */


/**
 *  手动断开连接，关闭自动重连。
 */
+ (void)goOffline;


/**
 *  手动建立连接，开启自动重连。
 */
+ (void)goOnline;


/** @name 事务 */

/**
 更新当前路径下的数据。服务器数据将会在 block 中返回，我们所要做的就是在 block 中
 把数据改成你要想要的，然后返回到 WTransactionResult 中。
 
 如果这个节点数据发送到服务器上时已经被其他人修改过，那么这个 block 将会获取服务器
 最新数据再次执行。
 
 调用 [WTransactionResult abort] 可以取消这次操作。
 事例：
 
    Wilddog *ref = [[Wilddog alloc] initWithUrl:@"https://<your-appid>.wilddogio.com"];
    [[ref childByAppendingPath:@"followNumber"] runTransactionBlock:^WTransactionResult *(WMutableData *currentData)  {
    NSNumber *value = currentData.value;
    if (currentData.value == nil) {
        value = @1;
    }else{
        [currentData setValue:[NSNumber numberWithInt:(1 + [value intValue])]];
    }
    return [WTransactionResult successWithValue:currentData];
 
    }];

 
  @param block   块(block)接收的当前数据(currentData)，然后返回一个WTransactionResult对象。
 */

- (void)runTransactionBlock:(WTransactionResult* (^) (WMutableData* currentData))block;


/**
 更新当前路径下的数据。服务器数据将会在 block 中返回，我们所要做的就是在 block 中
 把数据改成你要想要的，然后返回到 WTransactionResult 中。
 
 如果这个节点数据发送到服务器上时已经被其他人修改过，那么这个 block 将会获取服务器
 最新数据再次执行。
 
 调用 [FTransactionResult abort] 可以取消这次操作。 
 
 @param block    块(block)接收的当前数据(currentData)，然后返回一个WTransactionResult对象。
 
 @param completionBlock 当事务完成时这个块将被触发，无论成功与否。
 */
- (void)runTransactionBlock:(WTransactionResult* (^) (WMutableData* currentData))block andCompletionBlock:(void (^) (NSError *__nullable error, BOOL committed, WDataSnapshot *__nullable snapshot))completionBlock;


/**
 更新当前路径下的数据。服务器数据将会在 block 中返回，我们所要做的就是在 block 中
 把数据改成你要想要的，然后返回到 WTransactionResult 中。
 
 如果这个节点数据发送到服务器上时已经被其他人修改过，那么这个 block 将会获取服务器
 最新数据再次执行。
 
 调用 [FTransactionResult abort] 可以取消这次操作。
 
  @param block    块(block)接收的当前数据(currentData)，然后返回一个WTransactionResult对象。
  @param completionBlock 当事务完成时这个块将被触发，无论成功与否。
  @param localEvents  将其设置为 NO 来阻止触发中间状态的事件，只触发最终状态事件。
 */
- (void)runTransactionBlock:(WTransactionResult* (^) (WMutableData* currentData))block andCompletionBlock:(nullable void (^) (NSError *__nullable error, BOOL committed, WDataSnapshot *__nullable snapshot))completionBlock withLocalEvents:(BOOL)localEvents;


/** @name 检索字符串描述 */


/**
 *  获取当前Wilddog数据库节点的绝对URL。
 *
 *  @return 当前Wilddog数据库节点的绝对URL
 */
- (NSString *)description;


/** @name 属性 */

/**
 *  获取父节点的引用。如果当前节点就是root节点，方法执行后返回的依然是root节点的引用。
 */
@property (strong, readonly, nonatomic, nullable) Wilddog *parent;


/**
 *  获得Wilddog根结点的引用。
 */
@property (strong, readonly, nonatomic) Wilddog *root;


/**
 *  获得当前路径下节点的名称。
 */
@property (strong, readonly, nonatomic) NSString *key;


/**
 *  根据引用获得 WilddogApp 实例。
 */
@property (strong, readonly, nonatomic) WilddogApp *app;


/** @name 全局配置和设置 */


/**
 *  打印程序相关信息
 *
 *  @param enabled 设为YES为打印。默认为NO，不打印
 */
+ (void)setLoggingEnabled:(BOOL)enabled;

/**
 *  返回 Wilddog SDK 版本号。
 *
 *  @return Wilddog SDK版本号
 */
+ (NSString *)sdkVersion;


/** 
 *  返回默认的配置对象，用于配置客户端。
 *
 *  @return 默认的配置对象
 */
+ (WConfig *)defaultConfig;


/**
 *  为事件blocks 设置默认队列。
 *
 *  @param queue 给所有的Wilddog事件类型设置的默认队列
 */
+ (void)setDispatchQueue:(dispatch_queue_t)queue __attribute__((deprecated("Use [Wilddog defaultConfig].callbackQueue instead")));


@end

NS_ASSUME_NONNULL_END
