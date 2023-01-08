const std = @import("std");
const sha256 = std.crypto.hash.sha2.Sha256;

pub fn main() !noreturn {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    const args = try std.process.argsAlloc(allocator);
    defer std.process.argsFree(allocator, args);
    const input = args[1];
    comptime var seed: u64 = 10_000_000;
    comptime var i = 0;
    inline while (i < 8) : (i += 1) {
        const thread = try std.Thread.spawn(.{}, calculate, .{seed, input});
        thread.detach();
        seed <<= 2;
    }
    while (true) {}
}

fn calculate(input_seed: u64, input: [:0] const u8) !void {
    var seed = input_seed;
    const limit = seed << 2;
    var result: [sha256.digest_length]u8 = undefined;
    var seed_buffer: [30]u8 = undefined;
    var buffer: [100]u8 = undefined;
    while (seed < limit) : (seed += 1) {
        const seed_str = std.fmt.bufPrintIntToSlice(&seed_buffer, seed, 10, std.fmt.Case.lower, .{});
        const sha_input = try std.fmt.bufPrint(&buffer, "{s}{s}", .{input, seed_str});
        sha256.hash(sha_input, &result, .{});
        if (result[0] == 0 and result[1] == 0 and result[2] == 0 and result[3] > 31 and result[3] < 64) {
            std.debug.print("Append: {s}\n", .{seed_str});
            for (result) |val| {
                std.debug.print("{x:0^2}", .{val});
            }
            std.debug.print("\n", .{});
            std.os.exit(0);
        }
    }
}
