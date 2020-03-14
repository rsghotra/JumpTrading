# JumpTrading
Order Matching Engine

Class Description:

OrderReceiver: Receives order, analyze it and send to OrderMatcher class.
OrderMatcher: Receives processed order data from OrderReceiver class. if order is of 'aggressive nature' OrderMatcher class delegates the data to AgressiveOrderMatcher class.
AggressiveOrderMatcher: Pursue aggressive order matching strategies to fill the order asap.
OrderExecuter: After getting go from Matcher class. OrderExecuter class pulls the trigger.
CancelOrderRequest: Cancels the order.
