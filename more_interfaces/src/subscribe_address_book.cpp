#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "more_interfaces/msg/address_book.hpp"

using std::placeholders::_1;

class MinimalAddressSubscriber : public rclcpp::Node
{
public:
  MinimalAddressSubscriber()
  : Node("minimal_address_subscriber")
  {
    subscription_ = this->create_subscription<more_interfaces::msg::AddressBook>(    
      "address_book", 10, std::bind(&MinimalAddressSubscriber::topic_callback, this, _1));
  }

private:
  void topic_callback(const more_interfaces::msg::AddressBook &msg) const  
  {
    RCLCPP_INFO_STREAM(this->get_logger(), "Phone number is: '" << msg.phone_number << "'");     
  }
  rclcpp::Subscription<more_interfaces::msg::AddressBook>::SharedPtr subscription_;  
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalAddressSubscriber>());
  rclcpp::shutdown();
  return 0;
}