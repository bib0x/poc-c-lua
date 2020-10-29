local cfunctions = require "cfunctions"

-- List network interfaces
print("===== BEGIN print_ifaces ====")
cfunctions.print_ifaces()
print("===== END print_ifaces ====")

-- Print ip address
local interface = "enp3s0"
ret = cfunctions.get_network_info_ret(interface)
message = string.format("get_network_info_ret => %s: %s", interface, ret)
print(message)

-- Print result from network interface down
interface = "virbr0-nic"
ret = cfunctions.get_network_info_ret(interface)
if ret == nil then
    message = string.format("get_network_info_ret => %s down", interface)
    print(message)
end
