using Microsoft.AspNetCore.SignalR;
using Microsoft.Extensions.Logging;

namespace RealTimeCloud.Hubs
{
    public class RotationHub : Hub
    {
        private readonly ILogger<RotationHub> _logger;

        public RotationHub(ILogger<RotationHub> logger)
        {
            _logger = logger;
        }

        public async void LockAxis(string axis)
        {
            _logger.LogInformation("LockAxis", axis);
            await Clients.Others.SendCoreAsync("controlLocked", new [] { axis });
        }

        public async void UnlockAxis(string axis)
        {
            _logger.LogInformation("UnlockAxis", axis);
            await Clients.Others.SendCoreAsync("controlUnlocked", new [] { axis });
        }

        public async void RotateOnAxis(string axis, string value)
        {
            _logger.LogInformation("RotateOnAxis", axis);
            await Clients.Others.SendCoreAsync("rotated", new string[] { axis, value });
        }
    }
}